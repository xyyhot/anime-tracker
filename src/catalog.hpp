// catalog.hpp — 内置番库：写死的种子数据，作为"全网番剧"的离线简化版。
// 真实项目中这部分会换成 Jikan API 在线查询（见 README 路线图第三阶段）。
#pragma once

#include <vector>
#include <string>
#include "models.hpp"

namespace {

// 一个小工具函数：按参数构造 Anime，让下面的种子数据看起来更整齐
Anime makeAnime(std::string id, std::string zh, std::string en, int eps,
                std::string season, std::vector<std::string> genres) {
    Anime a;
    a.id = std::move(id);
    a.titleZh = std::move(zh);
    a.titleEn = std::move(en);
    a.totalEpisodes = eps;
    a.season = std::move(season);
    a.genres = std::move(genres);
    return a;
}

} // namespace

// 返回内置番库（静态变量：整个程序只构造一次）
inline const std::vector<Anime>& catalog() {
    static const std::vector<Anime> lib = {
        makeAnime("frieren",      "葬送的芙莉莲",           "Frieren: Beyond Journey's End", 28,  "2023秋", {"奇幻", "冒险", "治愈"}),
        makeAnime("aot",          "进击的巨人",             "Attack on Titan",              87,  "2013春", {"热血", "战斗", "悬疑"}),
        makeAnime("spyfamily",    "间谍过家家",             "Spy x Family",                 37,  "2022春", {"喜剧", "日常", "动作"}),
        makeAnime("demon_slayer", "鬼灭之刃",               "Demon Slayer",                 55,  "2019春", {"热血", "战斗", "奇幻"}),
        makeAnime("oshinoko",     "【我推的孩子】",         "Oshi no Ko",                   24,  "2023春", {"偶像", "悬疑", "娱乐圈"}),
        makeAnime("jjk",          "咒术回战",               "Jujutsu Kaisen",               47,  "2020秋", {"热血", "战斗", "黑暗"}),
        makeAnime("bocchi",       "孤独摇滚！",             "Bocchi the Rock!",             12,  "2022秋", {"音乐", "日常", "喜剧"}),
        makeAnime("chainsawman",  "电锯人",                 "Chainsaw Man",                 12,  "2022秋", {"战斗", "黑暗奇幻", "致郁"}),
        makeAnime("edgerunners",  "赛博朋克：边缘行者",     "Cyberpunk: Edgerunners",       10,  "2022秋", {"科幻", "战斗", "致郁"}),
        makeAnime("mushoku",      "无职转生",               "Mushoku Tensei",               23,  "2021冬", {"异世界", "冒险", "奇幻"}),
        makeAnime("deathnote",    "死亡笔记",               "Death Note",                   37,  "2006秋", {"悬疑", "智斗", "超自然"}),
        makeAnime("fmab",         "钢之炼金术师FA",         "Fullmetal Alchemist: Brotherhood", 64, "2009春", {"冒险", "热血", "奇幻"}),
        makeAnime("haikyuu",      "排球少年",               "Haikyuu!!",                    85,  "2014春", {"运动", "热血", "青春"}),
        makeAnime("cowboybebop",  "星际牛仔",               "Cowboy Bebop",                 26,  "1998",   {"科幻", "太空", "经典"}),
        makeAnime("gintama",      "银魂",                   "Gintama",                      201, "2006春", {"搞笑", "日常", "热血"}),
        makeAnime("summertime",   "夏日重现",               "Summer Time Rendering",        25,  "2022春", {"悬疑", "轮回", "奇幻"}),
        makeAnime("lycoris",      "莉可丽丝",               "Lycoris Recoil",               13,  "2022夏", {"动作", "日常", "百合"}),
        makeAnime("kaguya",       "辉夜大小姐想让我告白",   "Kaguya-sama: Love Is War",     37,  "2019冬", {"恋爱", "喜剧", "校园"}),
        makeAnime("steinsgate",   "命运石之门",             "Steins;Gate",                  24,  "2011春", {"科幻", "悬疑", "时间旅行"}),
        makeAnime("violet",       "紫罗兰永恒花园",         "Violet Evergarden",            13,  "2018冬", {"治愈", "奇幻", "文学"}),
        makeAnime("kaiju8",       "怪兽8号",                "Kaiju No. 8",                  12,  "2024春", {"战斗", "科幻", "怪兽"}),
        makeAnime("dungeonmeshi", "迷宫饭",                 "Delicious in Dungeon",         24,  "2024冬", {"奇幻", "冒险", "美食"}),
        makeAnime("mobpsycho",    "灵能百分百",             "Mob Psycho 100",               37,  "2016夏", {"超能力", "热血", "搞笑"}),
        makeAnime("one_punch",    "一拳超人",               "One-Punch Man",                24,  "2015秋", {"搞笑", "热血", "战斗"}),
        makeAnime("rezero",       "Re:从零开始的异世界生活", "Re:Zero",                      25,  "2016春", {"异世界", "轮回", "悬疑"}),
        makeAnime("konosuba",     "为美好的世界献上祝福",   "Konosuba",                     20,  "2016冬", {"搞笑", "异世界", "奇幻"}),
    };
    return lib;
}
