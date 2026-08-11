// http.cpp — WinINET 网络请求实现
#include "http.hpp"

#include <windows.h>
#include <wininet.h>

#include <stdexcept>
#include <string>

namespace {

// 发送一次请求的核心逻辑（不重试）
std::string httpPostOnce(const std::string& url, const std::string& body,
                         const std::string& contentType) {
    // 只支持 https:// 开头的 URL
    const std::string prefix = "https://";
    if (url.rfind(prefix, 0) != 0)
        throw std::runtime_error("仅支持 https:// 开头的 URL");

    // 拆出主机名和路径
    size_t pathPos = url.find('/', prefix.size());
    std::string host = pathPos == std::string::npos
                           ? url.substr(prefix.size())
                           : url.substr(prefix.size(), pathPos - prefix.size());
    std::string path = pathPos == std::string::npos ? "/" : url.substr(pathPos);

    // 打开会话（这里的名字会作为 User-Agent 发给服务器）
    HINTERNET hNet = InternetOpenA("anime-tracker/1.0", INTERNET_OPEN_TYPE_PRECONFIG,
                                   nullptr, nullptr, 0);
    if (!hNet)
        throw std::runtime_error("InternetOpen 失败，错误码 " + std::to_string(GetLastError()));

    HINTERNET hConn = InternetConnectA(hNet, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT,
                                       nullptr, nullptr, INTERNET_SERVICE_HTTP, 0, 0);
    if (!hConn) {
        InternetCloseHandle(hNet);
        throw std::runtime_error("InternetConnect 失败，错误码 " + std::to_string(GetLastError()));
    }

    std::string headers = "Content-Type: " + contentType + "\r\n";
    HINTERNET hReq = HttpOpenRequestA(hConn, "POST", path.c_str(), nullptr, nullptr, nullptr,
                                      INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD, 0);
    if (!hReq) {
        InternetCloseHandle(hConn);
        InternetCloseHandle(hNet);
        throw std::runtime_error("HttpOpenRequest 失败，错误码 " + std::to_string(GetLastError()));
    }

    if (!HttpSendRequestA(hReq, headers.c_str(), static_cast<DWORD>(headers.size()),
                          const_cast<char*>(body.data()), static_cast<DWORD>(body.size()))) {
        InternetCloseHandle(hReq);
        InternetCloseHandle(hConn);
        InternetCloseHandle(hNet);
        throw std::runtime_error("网络请求失败（连不上服务器？），错误码 " +
                                 std::to_string(GetLastError()));
    }

    // 循环读取响应体
    std::string result;
    char buf[4096];
    DWORD read = 0;
    while (InternetReadFile(hReq, buf, sizeof(buf), &read) && read > 0)
        result.append(buf, read);

    InternetCloseHandle(hReq);
    InternetCloseHandle(hConn);
    InternetCloseHandle(hNet);
    return result;
}

} // namespace

std::string httpPost(const std::string& url, const std::string& body,
                     const std::string& contentType) {
    // 简单重试：网络/代理偶尔抖动，失败时等 1 秒再试，最多 3 次
    std::string lastErr;
    for (int attempt = 1; attempt <= 3; ++attempt) {
        try {
            return httpPostOnce(url, body, contentType);
        } catch (const std::exception& e) {
            lastErr = e.what();
            if (attempt < 3) Sleep(1000);
        }
    }
    throw std::runtime_error(lastErr);
}
