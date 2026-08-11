# anime-tracker 追番进度表

一个用 C++17 写的命令行追番管理工具：搜索番剧、记录进度、打分、管理状态。数据自动保存为 JSON 文件，下次启动自动恢复。

> 第一阶段：纯 C++ 命令行 + JSON 本地存储（零第三方网络依赖）。
> 路线图：见文末。

## 功能

- `search` 在 26 部内置热门番中搜索（支持中文名 / 英文名 / 类型）
- `add` / `remove` 管理自己的追番列表
- `watch` 记录看到第几集
- `finish` / `drop` / `resume` 切换状态（在看 / 看过 / 弃番）
- `rate` 打分（0~10）
- `stats` 查看统计（各部数、平均评分）
- 所有修改实时保存到 `data/mylist.json`，重启不丢

## 环境要求

- Windows + MinGW-w64（g++ 支持 C++17），或 Visual Studio
- 推荐使用 **Windows Terminal** 运行（中文显示效果最好）

## 编译运行

```bat
:: 方法一：双击 build.bat（一键编译）
build.bat

:: 方法二：手动编译
g++ -std=c++17 -Wall -O2 src\main.cpp src\storage.cpp -Iinclude -o build\anime_tracker.exe

:: 运行
build\anime_tracker.exe
```

## 命令速查

| 命令 | 说明 |
|---|---|
| `search 芙莉莲` / `search frieren` | 在番库中搜索 |
| `add frieren` | 加入追番列表（状态:在看） |
| `list` | 显示我的列表 |
| `watch frieren` | 进度 +1 |
| `watch frieren 10` | 进度设为第 10 集 |
| `finish frieren` | 标记已看完 |
| `drop frieren` / `resume frieren` | 弃番 / 重新在看 |
| `rate frieren 9` | 打分 |
| `remove frieren` | 从列表移除 |
| `stats` | 统计 |
| `help` / `quit` | 帮助 / 退出 |

## 项目结构

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

## 你在这个项目里能学到

- **类与结构体**：`Anime` 的数据组织方式
- **STL**：`std::vector`、`std::map`、`std::string`、结构化绑定
- **文件 IO**：`ifstream` / `ofstream` 持久化
- **JSON 序列化**：`to_json` / `from_json` 的运作方式
- **枚举与错误处理**：`enum class`、`try/catch`、边界检查
- **模块划分**：头文件声明与 .cpp 实现的分离

## 路线图

- [x] 第一阶段：命令行版 + JSON 存储（当前）
- [ ] 第二阶段：Qt 图形界面（复用现有引擎）
- [ ] 第三阶段：接 Jikan API 在线搜索番剧

## 提示

- 源码全部是 UTF-8 编码。在 VS Code 中打开时若出现中文乱码，把编码切到 UTF-8。
- 想改数据？直接编辑 `data/mylist.json` 再启动即可（JSON 是带缩进的人类可读格式）。
- 建议现在就去装 Git，`git init` 把这个项目纳入版本管理——这是简历上要写的技能。
