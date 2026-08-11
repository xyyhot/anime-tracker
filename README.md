# 🎬 anime-tracker 追番进度表

> 一个用 **C++17** 写的命令行追番管理工具：搜索番剧、记录进度、打分、管理状态。
> 数据实时保存为 JSON 文件，重启不丢。从自己的追番习惯出发做的练手项目。

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![Windows](https://img.shields.io/badge/Windows-10%2F11-0078d6)
![JSON](https://img.shields.io/badge/storage-JSON-orange)

## ✨ 功能特性

- 🔍 **搜索**：内置 26 部热门番剧，支持中文名 / 英文名 / 类型模糊匹配（如 `search 奇幻`）
- 📝 **进度管理**：记录看到第几集、打分（0~10）、切换状态（在看 / 看过 / 弃番）
- 💾 **自动保存**：所有修改实时写入 `data/mylist.json`，人类可读、可手动编辑
- 📊 **统计**：查看各部数量、平均评分

## 🖥️ 运行效果

```
====================================
   anime-tracker 追番进度表 v1.0
   数据保存: data/mylist.json
====================================

anime> search frieren
  frieren | 葬送的芙莉莲 (Frieren: Beyond Journey's End) | 2023秋 | 28集 | 奇幻/冒险/治愈
共找到 1 部。

anime> add frieren
已加入追番: 葬送的芙莉莲（2023秋）

anime> watch frieren 10
葬送的芙莉莲 → 看到 10/28 集

anime> list
我的追番列表（共 1 部）
[在看] 1 部：
  frieren | 葬送的芙莉莲 | 10/28 | 评分 9

anime> quit
再见，下次再追番！
```

## 🚀 快速开始

**环境要求**：Windows + MinGW-w64（g++ 支持 C++17），或 Visual Studio。推荐用 **Windows Terminal** 运行，中文显示效果最好。

```bat
:: 方法一：双击 build.bat（一键编译）
build.bat

:: 方法二：手动编译
g++ -std=c++17 -Wall -O2 src\main.cpp src\storage.cpp -Iinclude -o build\anime_tracker.exe

:: 运行
build\anime_tracker.exe
```

## 📖 命令速查

| 命令 | 说明 |
|---|---|
| `search 芙莉莲` / `search frieren` | 在番库中搜索（支持中文/英文/类型） |
| `add frieren` | 加入追番列表（状态:在看） |
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
| nlohmann/json | 数据序列化（单头文件，零依赖） |
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
│   ├── catalog.hpp          内置番库种子数据（26 部）
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

## 🗺️ 路线图

- [x] **第一阶段**：命令行版 + JSON 本地存储
- [ ] **第二阶段**：Qt 图形界面（复用现有引擎）
- [ ] **第三阶段**：接入 Jikan API 在线搜索番剧

## 💡 使用小贴士

- 源码为 UTF-8 编码，在 VS Code 中打开如遇乱码请切换编码
- 想手动改数据？直接编辑 `data/mylist.json` 再启动即可
- 构建产物（`build/`）和个人数据（`data/`）已被 `.gitignore` 排除，不会上传
