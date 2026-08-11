// models.hpp — 数据模型：一部动漫长什么样，如何存成 JSON
#pragma once

#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
#include <nlohmann/json.hpp>

// 追番状态：在看 / 看过 / 弃番
enum class Status { Watching, Completed, Dropped };

// 一部动漫。既用于内置番库（progress/rating/status 用默认值），
// 也用于"我的追番列表"（这些字段记录我的真实进度）。
struct Anime {
    std::string id;                  // 唯一英文标识，如 "frieren"
    std::string titleZh;             // 中文名
    std::string titleEn;             // 英文/罗马音名，方便搜索
    int totalEpisodes = 0;           // 总集数，0 表示连载中/未知
    std::string season;              // 首播季度，如 "2023秋"
    std::vector<std::string> genres; // 类型标签
    int progress = 0;                // 我看到第几集
    int rating = 0;                  // 我的评分 0~10，0 表示未打分
    Status status = Status::Watching;

    // 关键字是否命中（匹配中文名 / 英文名 / id / 类型）
    bool matches(const std::string& kw) const;
};

// Status 与字符串互相转换（JSON 里存中文，方便人读；也接受英文以防万一）
inline std::string statusName(Status s) {
    switch (s) {
        case Status::Watching:  return "在看";
        case Status::Completed: return "看过";
        case Status::Dropped:   return "弃番";
    }
    return "未知";
}

inline Status parseStatus(const std::string& s) {
    if (s == "在看" || s == "watching")  return Status::Watching;
    if (s == "看过" || s == "completed") return Status::Completed;
    if (s == "弃番" || s == "dropped")   return Status::Dropped;
    throw std::runtime_error("无效的状态: " + s);
}

inline bool Anime::matches(const std::string& kw) const {
    // 英文部分统一转小写再匹配，这样搜 "FRIEREN" 也能命中
    auto lower = [](std::string s) {
        for (char& c : s)
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        return s;
    };
    std::string k = lower(kw);
    if (lower(id).find(k) != std::string::npos)      return true;
    if (lower(titleEn).find(k) != std::string::npos) return true;
    if (titleZh.find(k) != std::string::npos)        return true; // 中文无大小写，直接用
    for (const auto& g : genres)
        if (lower(g).find(k) != std::string::npos) return true;
    return false;
}

// nlohmann::json 要求的序列化接口：告诉它 Anime 怎么变成 JSON / 怎么从 JSON 恢复
inline void to_json(nlohmann::json& j, const Anime& a) {
    j = nlohmann::json{
        {"id", a.id},
        {"titleZh", a.titleZh},
        {"titleEn", a.titleEn},
        {"totalEpisodes", a.totalEpisodes},
        {"season", a.season},
        {"genres", a.genres},
        {"progress", a.progress},
        {"rating", a.rating},
        {"status", statusName(a.status)}
    };
}

inline void from_json(const nlohmann::json& j, Anime& a) {
    j.at("id").get_to(a.id);
    j.at("titleZh").get_to(a.titleZh);
    j.at("titleEn").get_to(a.titleEn);
    j.at("totalEpisodes").get_to(a.totalEpisodes);
    j.at("season").get_to(a.season);
    j.at("genres").get_to(a.genres);
    j.at("progress").get_to(a.progress);
    j.at("rating").get_to(a.rating);
    a.status = parseStatus(j.at("status").get<std::string>());
}
