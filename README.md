# 🎬 anime-tracker 追番进度表

> 一个用 **C++17** 写的命令行追番管理工具：**在线搜索番剧**、记录进度、打分、管理状态。
> 数据实时保存为 JSON 文件，重启不丢。从自己的追番习惯出发做的练手项目。

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![Windows](https://img.shields.io/badge/Windows-10%2F11-0078d6)
![JSON](https://img.shields.io/badge/storage-JSON-orange)
![License](https://img.shields.io/badge/license-MIT-green)

## ✨ 功能特性

- 🔍 **在线搜索**：调用 AniList API 实时搜索全网番剧（推荐英文/罗马音关键词）；断网时自动回退内置 **100+ 部**番库（26 部中文 + 79 部热门番，支持中文/英文/类型搜索，使用中文搜索则只能搜索到本地番剧，使用英文搜索可以搜索到绝大部分番剧，故推荐用英文搜索）
- 📝 **进度管理**：记录看到第几集、打分（0~10）、切换状态（在看 / 看过 / 弃番）
- 💾 **自动保存**：所有修改实时写入 `data/mylist.json`，人类可读、可手动编辑
- 📊 **统计**：查看各部数量、平均评分

## 🖥️ 运行效果

```
====================================
   anime-tracker 追番进度表 v1.1
   数据保存: data/mylist.json
====================================

anime> search frieren
在线搜索到 5 部（AniList）：
  154587 | Frieren: Beyond Journey's End (Sousou no Frieren) | 2023 FALL | 28集 | Adventure/Drama/Fantasy
  ...
提示：输入 add <数字id> 加入列表，如 add 154587

anime> add 154587
已加入追番: Frieren: Beyond Journey's End（AniList 在线）

anime> watch 154587 10
Frieren: Beyond Journey's End → 看到 10/28 集

anime> list
我的追番列表（共 1 部）
[在看] 1 部：
  154587 | Frieren: Beyond Journey's End | 10/28 | 评分 9

anime> quit
再见，下次再追番！
```

## 🚀 快速开始

**环境要求**：Windows + MinGW-w64（g++ 支持 C++17），或 Visual Studio。推荐用 **Windows Terminal** 运行，中文显示效果最好。

```bat
第一步：
:: 方法一：双击 build.bat（一键编译）
build.bat

:: 方法二：手动编译
g++ -std=c++17 -Wall -O2 src\main.cpp src\storage.cpp src\http.cpp src\anilist.cpp -Iinclude -o build\anime_tracker.exe -lwininet

第二步：
:: 运行
build\anime_tracker.exe
```

## 📖 命令速查

| 命令 | 说明 |
|---|---|
| `search frieren` | 在线搜索番剧（英文/罗马音关键词） |
| `search 奇幻` | 中文/类型关键词走内置番库（离线可用） |
| `add 154587` | 按 AniList 数字 id 加入列表（也可用内置番库 id） |
| `list` | 显示我的追番列表（按状态分组） |
| `watch frieren` | 进度 +1 |
| `watch frieren 10` | 进度设为第 10 集 |
| `finish frieren` | 标记已看完 |
| `drop frieren` / `resume frieren` | 弃番 / 重新在看 |
| `rate frieren 9` | 打分（0~10） |
| `remove frieren` | 从列表移除 |
| `stats` | 我的追番统计 |
| `help` / `quit` | 帮助 / 退出 |

## 🧰 技术栈

| 技术 | 用途 |
|---|---|
| C++17 | 核心语言：类、STL、枚举、结构化绑定 |
| nlohmann/json | 数据序列化 + API 响应解析（单头文件，零依赖） |
| WinINET | Windows 自带的 HTTPS 网络库（无需安装任何依赖） |
| AniList API | 在线搜索数据源（GraphQL） |
| std::filesystem | 数据目录管理 |
| MinGW g++ | 编译构建（`build.bat` 一键脚本） |

## 📁 项目结构

```
anime-tracker/
├── build.bat                一键编译脚本
├── include/nlohmann/json.hpp   JSON 库（单头文件，无需安装）
├── src/
│   ├── main.cpp             入口 + 命令行交互循环
│   ├── models.hpp           Anime 结构体、状态枚举、JSON 序列化
│   ├── catalog.hpp          内置番库（100+ 部，离线回退用）
│   ├── anilist.hpp/.cpp     AniList API 客户端（在线搜索）
│   ├── http.hpp/.cpp        WinINET 网络请求封装（零依赖）
│   └── storage.hpp/.cpp     列表的保存与读取
└── data/mylist.json         你的数据（自动生成，可手动编辑）
```

## 🧠 这个项目能学到什么

- **类与结构体**：`Anime` 数据模型的设计
- **STL**：`std::vector`、`std::map`、`std::string`、结构化绑定
- **文件 IO**：`ifstream` / `ofstream` 数据持久化
- **JSON 序列化**：`to_json` / `from_json` 的运作机制
- **枚举与错误处理**：`enum class`、`try/catch`、边界检查
- **模块划分**：头文件声明与 .cpp 实现的分离

## 💡 使用小贴士

- 源码为 UTF-8 编码，在 VS Code 中打开如遇乱码请切换编码
- 想手动改数据？直接编辑 `data/mylist.json` 再启动即可
- 构建产物（`build/`）和个人数据（`data/`）已被 `.gitignore` 排除，不会上传

## 📄 许可

[MIT License](LICENSE) © 2026 xyyhot
