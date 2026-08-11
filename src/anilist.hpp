// anilist.hpp — AniList API 客户端：在线搜索番剧
// 用 GraphQL 查询，返回结构化的动漫信息；失败时抛 std::runtime_error
#pragma once

#include <string>
#include <vector>
#include "models.hpp"

// 在线搜索动漫（返回前 5 条，按人气排序）
// 失败（断网、服务器错误等）抛 std::runtime_error；无结果返回空 vector
std::vector<Anime> searchAnime(const std::string& keyword);

// 按 AniList 数字 id 获取一部动漫（用于 add <id>）
// 找不到 / 参数不合法 / 网络失败都返回 false
bool fetchAnimeById(const std::string& id, Anime& out);
