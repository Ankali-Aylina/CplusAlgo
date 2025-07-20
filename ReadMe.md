# 介绍

这是一个个人练习C++算法的仓库。

## 目录

- [环境配置](#环境配置)
- [构建](#构建)
- [特殊项目](#特殊项目)
- [算法](#算法)

## 环境配置

- [x] Visual Studio Code
- [x] minGW64 g++15.1.0 gdb 16.2
- [x] CMake 4.1.0-rc1
- [x] C++11

## 构建

- [x] 使用CMake构建项目

```cmake
cmake -G "MinGW Makefiles" -B build -S . && cmake --build .
```

- [x] 使用gdb调试程序

## 特殊项目

- [x] [envTest](./envTest) 检测环境配置
- [x] [000-CreateNewProject](./000-CreateNewProject/readme.md) 创建新项目

## 算法

- [x] [递归](./001-Recursion/src/main.cpp) 构建算法的基础，放第一个！(O v O)

