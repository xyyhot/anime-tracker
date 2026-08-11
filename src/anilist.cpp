// anilist.cpp — AniList API 客户端实现
#include "anilist.hpp"

#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>

#include "http.hpp"

namespace {

const std::string kApiUrl = "https://graphql.anilist.co";

// 从 JSON 对象里安全取值：key 不存在或值为 null 时返回默认值。
// AniList 的标题/集数经常是 null，直接 .get<>() 会抛异常。
std::string strOr(const nlohmann::json& obj, const char* key, const char* fallback) {
    if (obj.contains(key) && !obj[key].is_null()) return obj[key].get<std::string>();
    return fallback;
}

int intOr(const nlohmann::json& obj, const char* key, int fallback) {
    if (obj.contains(key) && !obj[key].is_null()) return obj[key].get<int>();
    return fallback;
}

// 把一个 AniList 返回的 Media JSON 对象转换成我们的 Anime
Anime fromMedia(const nlohmann::json& m) {
    Anime a;
    a.id = std::to_string(intOr(m, "id", 0));

    // AniList 有 3 个标题字段：english / romaji(罗马音) / native(日文)。
    // 项目没有日文字段，就用英文作主标题、罗马音作英文名。
    const auto& title = m.contains("title") && m["title"].is_object()
                            ? m["title"]
                            : nlohmann::json::object();
    a.titleZh = strOr(title, "english", "");
    if (a.titleZh.empty()) a.titleZh = strOr(title, "romaji", "未知标题");
    a.titleEn = strOr(title, "romaji", "");

    a.totalEpisodes = intOr(m, "episodes", 0);   // 缺失/连载中 → 0

    int year = intOr(m, "seasonYear", 0);
    std::string season = strOr(m, "season", "");
    a.season = year > 0 ? std::to_string(year) + (season.empty() ? "" : " " + season) : season;

    if (m.contains("genres") && m["genres"].is_array())
        for (const auto& g : m["genres"])
            if (!g.is_null()) a.genres.push_back(g.get<std::string>());
    return a;
}

// 把 GraphQL 请求发出去并解析成 JSON
nlohmann::json postGraphQL(const nlohmann::json& request) {
    return nlohmann::json::parse(httpPost(kApiUrl, request.dump(), "application/json"));
}

} // namespace

std::vector<Anime> searchAnime(const std::string& keyword) {
    // GraphQL：按关键词搜索，返回前 5 条（按人气排序）
    nlohmann::json request = {
        {"query", R"(query ($s: String) {
            Page(perPage: 5) {
                media(search: $s, type: ANIME, sort: POPULARITY_DESC) {
                    id title { romaji english } episodes seasonYear season genres
                }
            }
        })"},
        {"variables", {{"s", keyword}}}
    };
    nlohmann::json resp = postGraphQL(request);

    // GraphQL 层报错（如关键词非法）→ 当作无结果处理，不当作崩溃
    if (resp.contains("errors")) return {};

    std::vector<Anime> out;
    for (const auto& m : resp["data"]["Page"]["media"])
        out.push_back(fromMedia(m));
    return out;
}

bool fetchAnimeById(const std::string& id, Anime& out) {
    int numericId;
    try {
        numericId = std::stoi(id);          // 非数字 id 直接失败
    } catch (...) {
        return false;
    }

    nlohmann::json request = {
        {"query", R"(query ($id: Int) {
            Media(id: $id, type: ANIME) {
                id title { romaji english } episodes seasonYear season genres
            }
        })"},
        {"variables", {{"id", numericId}}}
    };

    nlohmann::json resp;
    try {
        resp = postGraphQL(request);
    } catch (...) {
        return false;                       // 断网/服务器错误 → 返回 false，让调用方提示
    }
    if (resp.contains("errors")) return false;

    const auto& media = resp["data"]["Media"];
    if (media.is_null()) return false;      // 该 id 不存在
    out = fromMedia(media);
    return true;
}
