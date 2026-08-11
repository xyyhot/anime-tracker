// catalog.hpp — 内置番库：26 部手写中文条目 + 79 部从 AniList 拉取的 Top 热门番。
// 作为"全网番剧"的离线简化版，在线搜索失败时自动回退到这里。
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
        // —— 以下为从 AniList 拉取的 Top 热门番剧（已补中文译名）——
        makeAnime("21459", "我的英雄学院", "Boku no Hero Academia", 13, "2016 SPRING", {"Action", "Adventure", "Comedy"}),
        makeAnime("11061", "全职猎人（2011）", "HUNTER×HUNTER (2011)", 148, "2011 FALL", {"Action", "Adventure", "Fantasy"}),
        makeAnime("21", "海贼王", "ONE PIECE", 0, "1999 FALL", {"Action", "Adventure", "Comedy", "Drama", "Fantasy"}),
        makeAnime("20605", "东京喰种", "Tokyo Ghoul", 12, "2014 SUMMER", {"Action", "Drama", "Horror", "Mystery", "Psychological", "Supernatural"}),
        makeAnime("20958", "进击的巨人 第二季", "Shingeki no Kyojin Season 2", 12, "2017 SPRING", {"Action", "Drama", "Fantasy", "Mystery"}),
        makeAnime("20", "火影忍者", "NARUTO", 220, "2002 FALL", {"Action", "Adventure", "Comedy", "Drama", "Fantasy", "Supernatural"}),
        makeAnime("11757", "刀剑神域", "Sword Art Online", 25, "2012 SUMMER", {"Action", "Adventure", "Fantasy", "Romance"}),
        makeAnime("99147", "进击的巨人 第三季", "Shingeki no Kyojin Season 3", 12, "2018 SUMMER", {"Action", "Drama", "Fantasy", "Mystery"}),
        makeAnime("21856", "我的英雄学院 第二季", "Boku no Hero Academia 2", 25, "2017 SPRING", {"Action", "Adventure", "Comedy"}),
        makeAnime("110277", "进击的巨人 最终季", "Shingeki no Kyojin: The Final Season", 16, "2021 WINTER", {"Action", "Drama", "Fantasy", "Mystery"}),
        makeAnime("101759", "约定的梦幻岛", "Yakusoku no Neverland", 12, "2019 WINTER", {"Drama", "Fantasy", "Horror", "Mystery", "Psychological", "Thriller"}),
        makeAnime("20755", "暗杀教室", "Ansatsu Kyoushitsu", 22, "2015 WINTER", {"Action", "Comedy", "Drama", "Supernatural"}),
        makeAnime("20665", "四月是你的谎言", "Shigatsu wa Kimi no Uso", 22, "2014 FALL", {"Drama", "Music", "Romance", "Slice of Life"}),
        makeAnime("104578", "进击的巨人 第三季 Part 2", "Shingeki no Kyojin Season 3 Part 2", 10, "2019 SPRING", {"Action", "Drama", "Fantasy", "Mystery"}),
        makeAnime("1735", "火影忍者疾风传", "NARUTO: Shippuuden", 500, "2007 WINTER", {"Action", "Adventure", "Comedy", "Drama", "Fantasy", "Supernatural"}),
        makeAnime("21234", "只有我不存在的城市", "Boku dake ga Inai Machi", 12, "2016 WINTER", {"Drama", "Mystery", "Psychological", "Supernatural", "Thriller"}),
        makeAnime("100166", "我的英雄学院 第三季", "Boku no Hero Academia 3", 25, "2018 SPRING", {"Action", "Adventure", "Comedy", "Drama"}),
        makeAnime("97940", "黑色五叶草", "Black Clover", 170, "2017 FALL", {"Action", "Adventure", "Comedy", "Fantasy"}),
        makeAnime("101291", "青春猪头少年不会梦到兔女郎学姐", "Seishun Buta Yarou wa Bunny Girl Senpai no Yume wo Minai", 13, "2018 FALL", {"Comedy", "Drama", "Mystery", "Psychological", "Romance", "Supernatural"}),
        makeAnime("105333", "石纪元", "Dr. STONE", 24, "2019 SUMMER", {"Action", "Adventure", "Comedy", "Sci-Fi"}),
        makeAnime("101348", "冰海战记", "VINLAND SAGA", 24, "2019 SUMMER", {"Action", "Adventure", "Drama"}),
        makeAnime("19815", "游戏人生", "No Game No Life", 12, "2014 SPRING", {"Adventure", "Comedy", "Ecchi", "Fantasy"}),
        makeAnime("4224", "龙与虎", "Toradora!", 25, "2008 FALL", {"Comedy", "Drama", "Romance", "Slice of Life"}),
        makeAnime("20447", "野良神", "Noragami", 12, "2014 WINTER", {"Action", "Adventure", "Comedy", "Supernatural"}),
        makeAnime("20613", "斩·赤红之瞳！", "Akame ga Kill!", 24, "2014 SUMMER", {"Action", "Adventure", "Drama", "Fantasy", "Horror", "Psychological", "Thriller"}),
        makeAnime("124080", "堀与宫村", "Horimiya", 13, "2021 WINTER", {"Comedy", "Romance", "Slice of Life"}),
        makeAnime("104276", "我的英雄学院 第四季", "Boku no Hero Academia 4", 25, "2019 FALL", {"Action", "Adventure", "Comedy", "Drama", "Sci-Fi"}),
        makeAnime("20789", "七大罪", "Nanatsu no Taizai", 24, "2014 FALL", {"Action", "Adventure", "Comedy", "Ecchi", "Fantasy", "Supernatural"}),
        makeAnime("269", "死神", "BLEACH", 366, "2004 FALL", {"Action", "Adventure", "Supernatural"}),
        makeAnime("20623", "寄生兽", "Kiseijuu: Sei no Kakuritsu", 24, "2014 FALL", {"Action", "Drama", "Horror", "Psychological", "Sci-Fi"}),
        makeAnime("99423", "国家队", "Darling in the Franxx", 24, "2018 WINTER", {"Action", "Drama", "Mecha", "Psychological", "Romance", "Sci-Fi"}),
        makeAnime("1575", "反叛的鲁路修", "Code Geass: Hangyaku no Lelouch", 25, "2006 FALL", {"Action", "Drama", "Mecha", "Sci-Fi", "Thriller"}),
        makeAnime("30", "新世纪福音战士", "Shin Seiki Evangelion", 26, "1995 FALL", {"Action", "Drama", "Mecha", "Mystery", "Psychological", "Sci-Fi"}),
        makeAnime("145064", "咒术回战 第二季", "Jujutsu Kaisen 2nd Season", 23, "2023 SUMMER", {"Action", "Drama", "Supernatural"}),
        makeAnime("105310", "炎炎消防队", "Enen no Shouboutai", 24, "2019 SUMMER", {"Action", "Drama", "Sci-Fi", "Supernatural"}),
        makeAnime("142329", "鬼灭之刃 游郭篇", "Kimetsu no Yaiba: Yuukaku-hen", 11, "2022 WINTER", {"Action", "Adventure", "Fantasy", "Supernatural"}),
        makeAnime("14719", "JOJO的奇妙冒险", "JoJo no Kimyou na Bouken (TV)", 26, "2012 FALL", {"Action", "Adventure", "Supernatural"}),
        makeAnime("20931", "死亡游行", "Death Parade", 12, "2015 WINTER", {"Drama", "Mystery", "Psychological", "Supernatural", "Thriller"}),
        makeAnime("9919", "青之驱魔师", "Ao no Exorcist", 25, "2011 SPRING", {"Action", "Fantasy", "Supernatural"}),
        makeAnime("99263", "盾之勇者成名录", "Tate no Yuusha no Nariagari", 25, "2019 WINTER", {"Action", "Adventure", "Fantasy"}),
        makeAnime("101280", "关于我转生变成史莱姆这档事", "Tensei Shitara Slime Datta Ken", 24, "2018 FALL", {"Action", "Adventure", "Comedy", "Fantasy"}),
        makeAnime("98314", "狂赌之渊", "Kakegurui", 12, "2017 SUMMER", {"Drama", "Mystery", "Psychological"}),
        makeAnime("20594", "刀剑神域Ⅱ", "Sword Art Online II", 24, "2014 SUMMER", {"Action", "Adventure", "Fantasy", "Sci-Fi"}),
        makeAnime("98659", "欢迎来到实力至上主义的教室", "Youkoso Jitsuryoku Shijou Shugi no Kyoushitsu e", 12, "2017 SUMMER", {"Drama", "Psychological"}),
        makeAnime("120120", "东京复仇者", "Tokyo Revengers", 24, "2021 SPRING", {"Action", "Drama", "Romance", "Supernatural"}),
        makeAnime("6547", "天使的心跳", "Angel Beats!", 13, "2010 SPRING", {"Action", "Comedy", "Drama", "Supernatural"}),
        makeAnime("151807", "我独自升级", "Ore dake Level Up na Ken", 12, "2024 WINTER", {"Action", "Adventure", "Fantasy"}),
        makeAnime("131681", "进击的巨人 最终季 Part 2", "Shingeki no Kyojin: The Final Season Part 2", 12, "2022 WINTER", {"Action", "Drama", "Fantasy", "Mystery", "Psychological"}),
        makeAnime("112641", "辉夜大小姐想让我告白？", "Kaguya-sama wa Kokurasetai?: Tensaitachi no Renai Zunousen", 12, "2020 SPRING", {"Comedy", "Psychological", "Romance", "Slice of Life"}),
        makeAnime("20997", "夏洛特", "Charlotte", 13, "2015 SUMMER", {"Comedy", "Drama", "Romance", "Sci-Fi", "Supernatural"}),
        makeAnime("10620", "未来日记", "Mirai Nikki", 26, "2011 FALL", {"Action", "Horror", "Mystery", "Psychological", "Supernatural", "Thriller"}),
        makeAnime("132405", "更衣人偶坠入爱河", "Sono Bisque Doll wa Koi wo Suru", 12, "2022 WINTER", {"Comedy", "Ecchi", "Romance", "Slice of Life"}),
        makeAnime("21311", "文豪野犬", "Bungou Stray Dogs", 12, "2016 SPRING", {"Action", "Comedy", "Mystery", "Supernatural"}),
        makeAnime("18679", "斩服少女", "Kill la Kill", 24, "2013 FALL", {"Action", "Comedy", "Ecchi"}),
        makeAnime("117193", "我的英雄学院 第五季", "Boku no Hero Academia 5", 25, "2021 SPRING", {"Action", "Adventure", "Comedy", "Sci-Fi"}),
        makeAnime("20850", "东京喰种√A", "Tokyo Ghoul √A", 12, "2015 WINTER", {"Action", "Drama", "Horror", "Mystery", "Psychological", "Supernatural"}),
        makeAnime("97986", "来自深渊", "Made in Abyss", 13, "2017 SUMMER", {"Adventure", "Drama", "Fantasy", "Horror", "Mystery", "Sci-Fi"}),
        makeAnime("20923", "食戟之灵", "Shokugeki no Souma", 24, "2015 SPRING", {"Comedy", "Ecchi"}),
        makeAnime("20832", "不死者之王", "Overlord", 13, "2015 SUMMER", {"Action", "Adventure", "Fantasy"}),
        makeAnime("20992", "排球少年 第二季", "Haikyuu!! 2nd Season", 25, "2015 FALL", {"Comedy", "Drama", "Sports"}),
        makeAnime("15809", "打工吧！魔王大人", "Hataraku Maou-sama!", 13, "2013 SPRING", {"Comedy", "Fantasy", "Romance", "Slice of Life"}),
        makeAnime("20920", "在地下城寻求邂逅是否搞错了什么", "Dungeon ni Deai wo Motomeru no wa Machigatteiru Darou ka", 13, "2015 SPRING", {"Action", "Adventure", "Comedy", "Fantasy", "Romance"}),
        makeAnime("9989", "我们仍未知道那天所看见的花的名字", "Ano Hi Mita Hana no Namae wo Bokutachi wa Mada Shiranai.", 11, "2011 SPRING", {"Drama", "Romance", "Slice of Life", "Supernatural"}),
        makeAnime("3588", "噬魂师", "Soul Eater", 51, "2008 SPRING", {"Action", "Adventure", "Comedy", "Fantasy", "Supernatural"}),
        makeAnime("11111", "替身（Another）", "Another", 12, "2012 WINTER", {"Horror", "Mystery", "Psychological", "Supernatural", "Thriller"}),
        makeAnime("171018", "胆大党", "Dandadan", 12, "2024 FALL", {"Action", "Comedy", "Drama", "Romance", "Sci-Fi", "Supernatural"}),
        makeAnime("14813", "我的青春恋爱物语果然有问题", "Yahari Ore no Seishun Love Come wa Machigatteiru.", 13, "2013 SPRING", {"Comedy", "Drama", "Romance", "Slice of Life"}),
        makeAnime("6702", "妖精的尾巴", "FAIRY TAIL", 175, "2009 FALL", {"Action", "Adventure", "Comedy", "Fantasy"}),
        makeAnime("2001", "天元突破红莲螺岩", "Tengen Toppa Gurren Lagann", 27, "2007 SPRING", {"Action", "Comedy", "Drama", "Mecha", "Romance", "Sci-Fi"}),
        makeAnime("108632", "Re:从零开始的异世界生活 第二季", "Re:Zero kara Hajimeru Isekai Seikatsu 2nd Season", 13, "2020 SUMMER", {"Action", "Adventure", "Drama", "Fantasy", "Psychological", "Thriller"}),
        makeAnime("21699", "为美好的世界献上祝福！2", "Kono Subarashii Sekai ni Shukufuku wo! 2", 10, "2017 WINTER", {"Adventure", "Comedy", "Ecchi", "Fantasy"}),
        makeAnime("101347", "多罗罗", "Dororo", 24, "2019 WINTER", {"Action", "Adventure", "Drama", "Supernatural"}),
        makeAnime("145139", "鬼灭之刃 刀匠村篇", "Kimetsu no Yaiba: Katanakaji no Sato-hen", 11, "2023 SPRING", {"Action", "Adventure", "Drama", "Fantasy", "Supernatural"}),
        makeAnime("21170", "暗杀教室 第二季", "Ansatsu Kyoushitsu 2nd Season", 25, "2016 WINTER", {"Action", "Comedy", "Drama", "Supernatural"}),
        makeAnime("21698", "排球少年 第三季", "Haikyuu!!: Karasuno Koukou VS Shiratorizawa Gakuen Koukou", 10, "2016 FALL", {"Comedy", "Drama", "Sports"}),
        makeAnime("2904", "反叛的鲁路修 R2", "Code Geass: Hangyaku no Lelouch R2", 25, "2008 SPRING", {"Action", "Drama", "Mecha", "Sci-Fi", "Thriller"}),
        makeAnime("129874", "鬼灭之刃 无限列车篇", "Kimetsu no Yaiba: Mugen Ressha-hen (TV)", 7, "2021 FALL", {"Action", "Adventure", "Drama", "Fantasy", "Mystery", "Supernatural"}),
        makeAnime("128893", "地狱乐", "Jigokuraku", 13, "2023 SPRING", {"Action", "Adventure", "Mystery", "Supernatural"}),
        makeAnime("21804", "齐木楠雄的灾难", "Saiki Kusuo no Ψ-nan", 120, "2016 SUMMER", {"Comedy", "Slice of Life", "Supernatural"}),
    };
    return lib;
}
