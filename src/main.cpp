// main.cpp — 程序入口：命令行交互循环（REPL）
// 用法：输入 help 查看所有命令
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>   // SetConsoleOutputCP / SetConsoleCP
#endif

#include "anilist.hpp"
#include "catalog.hpp"
#include "models.hpp"
#include "storage.hpp"

namespace {

// Windows 下把控制台切到 UTF-8，让中文正常显示和输入
void setupConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

std::string trim(const std::string& s) {
    size_t b = s.find_first_not_of(" \t\r\n");
    if (b == std::string::npos) return "";
    size_t e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

std::string progressText(const Anime& a) {
    if (a.totalEpisodes <= 0) return std::to_string(a.progress) + "/连载中";
    return std::to_string(a.progress) + "/" + std::to_string(a.totalEpisodes);
}

std::string ratingText(const Anime& a) {
    return a.rating > 0 ? "评分 " + std::to_string(a.rating) : "未评分";
}

// 一行完整信息（用于 search 结果）
void printFullInfo(const Anime& a) {
    std::cout << "  " << a.id << " | " << a.titleZh << " (" << a.titleEn << ")"
              << " | " << a.season << " | " << a.totalEpisodes << "集";
    if (!a.genres.empty()) {
        std::cout << " | ";
        for (size_t i = 0; i < a.genres.size(); ++i) {
            if (i) std::cout << "/";
            std::cout << a.genres[i];
        }
    }
    std::cout << "\n";
}

// 在番库中按 id 精确查找；找不到返回 nullptr
const Anime* findInCatalog(const std::string& id) {
    for (const auto& a : catalog())
        if (a.id == id) return &a;
    return nullptr;
}

void printHelp() {
    std::cout << "\n可用命令：\n"
              << "  search <关键词>      在番库中搜索（支持中文名/英文名/类型）\n"
              << "  add <id>            把一部番加入追番列表（状态:在看）\n"
              << "  list                显示我的追番列表\n"
              << "  watch <id> [集数]   更新进度，不写集数则 +1\n"
              << "  finish <id>         标记为已看完\n"
              << "  drop <id>           弃番\n"
              << "  resume <id>         重新在看\n"
              << "  rate <id> <0-10>    打分\n"
              << "  remove <id>         从列表移除\n"
              << "  stats               我的追番统计\n"
              << "  help                显示本帮助\n"
              << "  quit / exit         退出\n"
              << "提示：先 search 找到想看的番，用它的 id 执行 add。\n";
}

void cmdSearch(const std::string& kw) {
    if (kw.empty()) {
        std::cout << "请输入关键词，例如: search frieren（在线）/ search 奇幻（内置番库）\n";
        return;
    }
    // 在线模式：调用 AniList API 搜索全网番剧
    try {
        auto results = searchAnime(kw);
        if (!results.empty()) {
            std::cout << "在线搜索到 " << results.size() << " 部（AniList）：\n";
            for (const auto& a : results) printFullInfo(a);
            std::cout << "提示：输入 add <数字id> 加入列表，如 add " << results.front().id << "\n";
            return;
        }
        std::cout << "API 无结果（在线搜索推荐用英文/罗马音关键词），改用内置番库：\n";
    } catch (const std::exception& e) {
        std::cout << "在线搜索失败（" << e.what() << "），改用内置番库（离线模式）：\n";
    }
    // 离线回退：内置番库
    int n = 0;
    for (const auto& a : catalog()) {
        if (a.matches(kw)) {
            printFullInfo(a);
            ++n;
        }
    }
    std::cout << "共找到 " << n << " 部。\n";
}

// 按状态分组显示我的列表
void cmdList(const MyList& list) {
    if (list.empty()) {
        std::cout << "列表还是空的。先 search 找一部想看的番，再 add <id>。\n";
        return;
    }
    std::vector<const Anime*> watching, completed, dropped;
    for (const auto& [id, a] : list) {
        switch (a.status) {
            case Status::Watching:  watching.push_back(&a);  break;
            case Status::Completed: completed.push_back(&a); break;
            case Status::Dropped:   dropped.push_back(&a);   break;
        }
    }
    std::cout << "我的追番列表（共 " << list.size() << " 部）\n";
    auto dump = [](const char* label, const std::vector<const Anime*>& v) {
        if (v.empty()) return;
        std::cout << "[" << label << "] " << v.size() << " 部：\n";
        for (const Anime* a : v)
            std::cout << "  " << a->id << " | " << a->titleZh << " | "
                      << progressText(*a) << " | " << ratingText(*a) << "\n";
    };
    dump("在看", watching);
    dump("看过", completed);
    dump("弃番", dropped);
}

void cmdAdd(MyList& list, const std::string& id) {
    if (id.empty()) { std::cout << "用法: add <id>\n"; return; }
    if (list.count(id)) { std::cout << id << " 已经在你的列表里了。\n"; return; }

    // 1) 内置番库精确匹配（离线也能用）
    if (const Anime* found = findInCatalog(id)) {
        list[id] = *found;                       // 从番库复制一份到我的列表
        list[id].status = Status::Watching;      // 加入即"在看"
        saveMyList(list);
        std::cout << "已加入追番: " << found->titleZh << "（内置番库）\n";
        return;
    }

    // 2) 数字 id → 尝试从 AniList 在线拉取
    if (std::all_of(id.begin(), id.end(), [](unsigned char c) { return std::isdigit(c); })) {
        try {
            Anime fromApi;
            if (fetchAnimeById(id, fromApi)) {
                list[id] = fromApi;
                list[id].status = Status::Watching;
                saveMyList(list);
                std::cout << "已加入追番: " << fromApi.titleZh << "（AniList 在线）\n";
                return;
            }
        } catch (const std::exception& e) {
            std::cout << "在线获取失败（" << e.what() << "）\n";
        }
        std::cout << "AniList 上找不到 id 为 " << id << " 的番剧。\n";
        return;
    }

    // 3) 都不是 → 给出建议
    std::cout << "番库中没有 id 为 " << id << " 的条目。相近结果：\n";
    int shown = 0;
    for (const auto& a : catalog())
        if (a.matches(id) && shown < 5) { printFullInfo(a); ++shown; }
    if (!shown)
        std::cout << "（无相近结果。提示：先 search 关键词在线搜索，再用返回的数字 id 执行 add）\n";
}

void cmdWatch(MyList& list, const std::string& id, int ep) {
    auto it = list.find(id);
    if (it == list.end()) { std::cout << id << " 不在你的列表中，先 add " << id << "\n"; return; }
    Anime& a = it->second;
    if (ep < 0) ep = a.progress + 1;         // 没写集数 → 自动 +1
    a.progress = ep;
    if (a.totalEpisodes > 0 && a.progress > a.totalEpisodes) {
        a.progress = a.totalEpisodes;
        std::cout << a.titleZh << " 已追到最后一集，可用 finish 标记完成。\n";
    }
    if (a.progress < 0) a.progress = 0;
    saveMyList(list);
    std::cout << a.titleZh << " → 看到 " << progressText(a) << " 集\n";
}

void cmdFinish(MyList& list, const std::string& id) {
    auto it = list.find(id);
    if (it == list.end()) { std::cout << id << " 不在你的列表中，先 add " << id << "\n"; return; }
    Anime& a = it->second;
    a.status = Status::Completed;
    if (a.totalEpisodes > 0) a.progress = a.totalEpisodes;
    saveMyList(list);
    std::cout << "恭喜看完: " << a.titleZh << " 🎉\n";
}

void cmdDrop(MyList& list, const std::string& id) {
    auto it = list.find(id);
    if (it == list.end()) { std::cout << id << " 不在你的列表中，先 add " << id << "\n"; return; }
    it->second.status = Status::Dropped;
    saveMyList(list);
    std::cout << "已弃番: " << it->second.titleZh << "\n";
}

void cmdResume(MyList& list, const std::string& id) {
    auto it = list.find(id);
    if (it == list.end()) { std::cout << id << " 不在你的列表中，先 add " << id << "\n"; return; }
    it->second.status = Status::Watching;
    saveMyList(list);
    std::cout << "重新在看: " << it->second.titleZh << "\n";
}

void cmdRate(MyList& list, const std::string& id, int score) {
    auto it = list.find(id);
    if (it == list.end()) { std::cout << id << " 不在你的列表中，先 add " << id << "\n"; return; }
    if (score < 0 || score > 10) { std::cout << "评分需在 0~10 之间\n"; return; }
    it->second.rating = score;
    saveMyList(list);
    std::cout << "已给 " << it->second.titleZh << " 打 " << score << " 分\n";
}

void cmdRemove(MyList& list, const std::string& id) {
    if (list.erase(id)) {
        saveMyList(list);
        std::cout << "已从列表移除: " << id << "\n";
    } else {
        std::cout << id << " 不在你的列表中。\n";
    }
}

void cmdStats(const MyList& list) {
    if (list.empty()) { std::cout << "列表为空，先 add 几部番吧。\n"; return; }
    int nWatch = 0, nDone = 0, nDrop = 0, ratedSum = 0, ratedCnt = 0;
    for (const auto& [id, a] : list) {
        switch (a.status) {
            case Status::Watching:  ++nWatch; break;
            case Status::Completed: ++nDone;  break;
            case Status::Dropped:   ++nDrop;  break;
        }
        if (a.rating > 0) { ratedSum += a.rating; ++ratedCnt; }
    }
    std::cout << "统计: 在看 " << nWatch << " 部 / 看过 " << nDone << " 部 / 弃番 "
              << nDrop << " 部";
    if (ratedCnt)
        std::cout << " | 平均评分 " << (static_cast<double>(ratedSum) / ratedCnt);
    std::cout << "\n";
}

} // namespace

int main() {
    setupConsole();
    std::filesystem::create_directories("data");   // 确保 data 目录存在

    MyList myList;
    loadMyList(myList);

    std::cout << "====================================\n"
              << "   anime-tracker 追番进度表 v1.1\n"
              << "   数据保存: " << kDataFile << "\n"
              << "====================================\n";
    printHelp();

    std::string line;
    while (true) {
        std::cout << "\nanime> ";
        std::getline(std::cin, line);
        if (!std::cin) break;                      // Ctrl+Z / Ctrl+D 退出

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        if (cmd.empty()) continue;

        if (cmd == "quit" || cmd == "exit") break;
        else if (cmd == "help") printHelp();
        else if (cmd == "list") cmdList(myList);
        else if (cmd == "search") {
            std::string rest;
            std::getline(iss, rest);
            cmdSearch(trim(rest));
        }
        else if (cmd == "add") {
            std::string id; iss >> id;
            cmdAdd(myList, id);
        }
        else if (cmd == "watch") {
            std::string id; int ep = -1;
            iss >> id;
            iss >> ep;                             // 读不到就保持 -1（自动 +1）
            cmdWatch(myList, id, ep);
        }
        else if (cmd == "finish") { std::string id; iss >> id; cmdFinish(myList, id); }
        else if (cmd == "drop")   { std::string id; iss >> id; cmdDrop(myList, id); }
        else if (cmd == "resume") { std::string id; iss >> id; cmdResume(myList, id); }
        else if (cmd == "rate") {
            std::string id; int score = 0;
            iss >> id >> score;
            cmdRate(myList, id, score);
        }
        else if (cmd == "remove") { std::string id; iss >> id; cmdRemove(myList, id); }
        else if (cmd == "stats")  cmdStats(myList);
        else std::cout << "未知命令: " << cmd << "（输入 help 查看用法）\n";
    }
    std::cout << "\n再见，下次再追番！\n";
    return 0;
}
