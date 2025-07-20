#include <iostream>
#include <filesystem> // 文件系统库
#include <string>
#include <vector>    // 动态数组容器
#include <optional>  // optional类型
#include <cctype>    // 用于 ::toupper 和字符处理
#include <algorithm> // 添加缺失的头文件 - 解决 transform 错误
#include <future>    // 异步操作支持
#include <vector>    // 动态数组容器
#include <fstream>   // 文件输入输出流

namespace fs = std::filesystem; // 别名简化
using namespace std;

string projectName;

/// @brief 检查项目名称是否合法
/// @param name 名字
/// @return
bool nameCheck(const string &name);

/// @brief 创建文件夹
/// @param parent_path  父目录路径
/// @param folderName 文件夹名称
/// @return 创建是否成功
bool createFolder(const fs::path &parent_path, const string &folderName);

/// @brief 在目录树中向上查找匹配的父文件夹
/// @param start_path 起始搜索路径
/// @param target_name 目标文件夹名称
/// @param find_all 否查找所有匹配项 (默认false)
/// @param stop_at_first 找到第一个匹配后是否停止 (默认false)
/// @return 包含匹配路径的optional对象 (找不到时返回std::nullopt)
optional<fs::path> findAimFolder(
    const fs::path &start_path, // 起始路径
    const string &target_name,
    bool find_all = false,
    bool stop_at_first = false);

/// @brief 并行复制文件
/// @param src 源路径
/// @param dst 目标路径
void copyFiles(const fs::path &src, const fs::path &dst);

/// @brief 创建CMakeLists.txt文件
/// @param parent_path 创建路径
/// @param projectName 项目名称
void createCMakeLists(const fs::path &parent_path, const string &projectName);

/// @brief 创建README.md文件
/// @param parent_path 创建路径
/// @param projectName 项目名称
void createReadme(const fs::path &parent_path, const string &projectName);
