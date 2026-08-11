// storage.hpp — 负责"我的追番列表"的保存与读取
#pragma once

#include <map>
#include <string>
#include "models.hpp"

// 我的追番列表：用 std::map 按 id 排序存放，查找/遍历都方便
using MyList = std::map<std::string, Anime>;

// 数据文件位置（相对于运行程序时的目录）
inline const std::string kDataFile = "data/mylist.json";

// 把整个列表保存到文件；成功返回 true
bool saveMyList(const MyList& list);

// 从文件读入列表；文件不存在时返回空列表（首次运行）
bool loadMyList(MyList& list);
