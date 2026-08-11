// storage.cpp — 数据持久化的实现：JSON 的读写
#include "storage.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

bool saveMyList(const MyList& list) {
    nlohmann::json root = nlohmann::json::array();
    for (const auto& [id, anime] : list)
        root.push_back(anime);          // Anime 会自动调用 to_json 变成 JSON 对象

    std::ofstream out(kDataFile);
    if (!out) {
        std::cerr << "无法写入文件: " << kDataFile << "\n";
        return false;
    }
    out << root.dump(2) << "\n";        // dump(2) 带缩进，方便用记事本查看和手动修改
    return true;
}

bool loadMyList(MyList& list) {
    list.clear();
    std::ifstream in(kDataFile);
    if (!in) return true;               // 文件还不存在 → 空列表，不算错误

    try {
        nlohmann::json root = nlohmann::json::parse(in);
        for (const auto& item : root) {
            Anime a = item.get<Anime>();    // 自动调用 from_json 恢复
            list[a.id] = std::move(a);
        }
    } catch (const std::exception& e) {
        std::cerr << "读取数据文件失败: " << e.what() << "\n";
        return false;
    }
    return true;
}
