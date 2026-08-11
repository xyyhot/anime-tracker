// http.hpp — 极简网络请求封装（基于 Windows 自带的 WinINET，零第三方依赖）
#pragma once

#include <string>

// 发送 HTTPS POST 请求，返回响应体文本。
// 失败（连不上、URL 不合法等）时抛出 std::runtime_error，由调用方决定如何处理。
std::string httpPost(const std::string& url, const std::string& body,
                     const std::string& contentType);
