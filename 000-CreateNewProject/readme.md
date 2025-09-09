# 000-CreateNewProject

## 简介

创建新的项目。

## 目录

- [功能](#功能)
- [使用环境](#使用环境)
- [创建的项目文件结构](#创建的项目文件结构)
- [项目文件说明](#项目文件说明)
- [函数说明](#函数说明)
- [构建及使用方法](#构建及使用方法)
- [注意事项](#注意事项)
- [帮助](#帮助)

## 功能

创建新的项目，包括创建项目文件夹、创建项目文件、创建项目配置文件等。

## 使用环境

Windows 10

## 创建的项目文件结构

```bash
项目名称/
├── .vscode/
│   ├── launch.json
│   └── tasks.json
├── include/
│   └── main.h
├── src/
│   └── main.cpp
├── CMakeLists.txt
└── readme.md
```

## 项目文件说明

- `.vscode/`：存放VS Code的配置文件。
- `include/`：存放头文件。
- `src/`：存放源文件。
- `CMakeLists.txt`：CMake的配置文件。
- `readme.md`：项目的说明文件。

## 函数说明

- `nameCheck`: 检查项目名称是否合法。
- `createFolder`: 创建文件夹。
- `copyFiles`: 复制文件。
- `createCMakeLists`: 创建CMakeLists.txt文件。
- `createReadme`: 创建readme.md文件。
- [详细的函数解释请参考源代码](./src/main.cpp)。

## 构建及使用方法

1. 使用CMake构建项目。

    ```cmake
    cmake -G "MinGW Makefiles" -B build -S . && cmake --build .
    ```

    - PS：需要安装CMake和MinGW,并且将MinGW的bin目录添加到环境变量中。建议在VS code中使用CMake插件，方便调试。

2. 直接运行000-CreateNewProject.exe即可。

## 注意事项

需要结合template文件夹使用，放在同一目录下，并且都位于000-CreateNewProject文件夹下。

## 帮助

详细代码解释见[源代码解释](https://ankali-aylina.github.io/2025/07/22/C-%E7%AE%97%E6%B3%95%E5%AD%A6%E4%B9%A0/)。
