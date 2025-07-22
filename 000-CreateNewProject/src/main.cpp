#include "main.h"

bool nameCheck(const string &name)
{
    if (name.empty())
    {
        std::cout << "文件夹名称不能为空！\n";
        return false;
    }

    // 检查非法字符 (Windows和Linux通用)
    const std::string invalid_chars = "<>:\"/\\|?*";
    // 遍历name中的每个字符
    for (char c : name)
    {
        if (invalid_chars.find(c) != std::string::npos)
        {
            std::cout << "名称包含非法字符: '" << c << "'\n";
            return false;
        }

        // 控制字符检查
        if (std::iscntrl(static_cast<unsigned char>(c)))
        {
            std::cout << "名称包含控制字符！\n";
            return false;
        }
    }

    // 检查保留名称 (Windows)
    const std::vector<std::string> reserved_names = {
        "CON", "PRN", "AUX", "NUL",
        "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9",
        "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9"};

    // 转换为大写以检查保留名称
    std::string upper_name = name;
    std::transform(upper_name.begin(), upper_name.end(), upper_name.begin(), ::toupper);

    for (const auto &reserved : reserved_names)
    {
        if (upper_name == reserved)
        {
            std::cout << "名称 '" << name << "' 是系统保留名称！\n";
            return false;
        }
    }

    // 检查开头和结尾的非法字符
    if (name.front() == ' ' || name.front() == '.')
    {
        std::cout << "名称不能以空格或点开头！\n";
        return false;
    }

    if (name.back() == ' ' || name.back() == '.')
    {
        std::cout << "名称不能以空格或点结尾！\n";
        return false;
    }

    // 检查名称长度
    if (name.length() > 255)
    {
        std::cout << "名称过长（最大255字符）！\n";
        return false;
    }

    return true;
}

bool createFolder(const fs::path &parent_path, const string &folderName)
{
    // 尝试创建文件夹
    try
    {
        // 拼接父路径和文件夹名称，得到创建路径
        fs::path createPath = parent_path / folderName;
        // 如果文件夹已存在，输出提示信息并返回false
        if (fs::exists(createPath))
        {
            cout << "文件夹已存在" << endl;
            return false;
        }

        // 如果创建文件夹成功，输出成功信息并返回true
        if (fs::create_directory(createPath))
        {
            cout << "成功创建文件夹: " << createPath << "\n";
            return true;
        }
        // 如果创建文件夹失败，输出失败信息并返回false
        cerr << "无法创建文件夹: " << createPath << "\n";
        return false;
    }
    // 捕获文件系统错误，输出错误信息并返回false
    catch (const fs::filesystem_error &e)
    {
        cerr << "文件系统错误: " << e.what() << "\n";
        return false;
    }

    // 如果没有成功创建文件夹，返回false
    return false;
}

optional<fs::path> findAimFolder(const fs::path &start_path, const string &target_name, bool find_all, bool stop_at_first)
{
    // 存储所有匹配路径的容器
    vector<fs::path> matches;

    // 获取绝对路径确保路径解析正确
    fs::path current = fs::absolute(start_path);

    // 记录根路径用于终止循环
    const fs::path root = current.root_path();

    // 最大向上搜索层数，限制深度
    int max_depth = 5;
    int current_depth = 0;

    // 循环向上遍历目录树
    while (current_depth++ < max_depth && current != root)
    {
        // 调试输出当前检查的路径 (实际使用时可以移除)
        // std::cout << "检查: " << current << std::endl;

        // 检查当前目录名是否匹配目标
        if (current.filename() == target_name)
        {
            // 将匹配路径添加到结果集
            matches.push_back(current);

            // 如果设置了找到即停止且不需要所有结果
            if (stop_at_first && !matches.empty())
            {
                return matches.front(); // 返回第一个匹配项
            }
        }

        // 到达根目录时停止遍历 (防止无限循环)
        if (current == root)
        {
            break;
        }

        // 获取父目录 (当已经是根目录时，parent_path()返回自身)
        fs::path parent = current.parent_path();

        // 检查是否无法继续向上 (文件系统保护机制)
        if (parent == current)
        {
            break;
        }

        // 移动到父目录继续搜索
        current = parent;
    }

    // 处理查找结果
    if (matches.empty())
    {
        // 没有找到匹配项
        return std::nullopt;
    }
    else if (find_all)
    {
        // 返回所有匹配路径 (实际实现需要修改返回类型)
        // 此处简化处理返回最近的一个匹配项
        return matches.back(); // 最近的祖先目录
    }
    else
    {
        // 默认返回最近(最上层)的匹配项
        return matches.back();
    }
}

void copyFiles(const fs::path &src, const fs::path &dst)
{
    std::vector<std::future<void>> futures; // 存储异步任务的结果

    // 原子计数器：用于线程安全的进度跟踪
    std::atomic<int> filesCopied = 0;       // 已复制的文件数
    std::atomic<int> directoriesCopied = 0; // 已复制的目录数
    std::atomic<int> tasksCompleted = 0;    // 新增：跟踪完成的任务数（含失败）
    std::atomic<int> copyErrors = 0;        // 新增：错误计数器
    std::mutex errorMutex;                  // 新增：保护错误输出

    // 获取开始时间（用于计算速度）
    auto startTime = std::chrono::steady_clock::now();

    auto showProgress = [&]()
    {
        const int totalTasks = futures.size();
        const int completed = tasksCompleted; // 使用tasksCompleted替代filesCopied+directoriesCopied

        auto duration = std::chrono::steady_clock::now() - startTime;
        double seconds = std::chrono::duration<double>(duration).count();
        double progress = (totalTasks > 0) ? (100.0 * completed / totalTasks) : 0.0;
        double speed = (seconds > 0.1) ? (filesCopied / seconds) : 0.0;

        std::cout << "\r进度: " << std::fixed << std::setprecision(1)
                  << progress << "% | "
                  << "文件: " << filesCopied
                  << " | 目录: " << directoriesCopied
                  << " | 错误: " << copyErrors // 显示错误计数
                  << " | 速度: " << std::setprecision(1) << speed << " 文件/秒"
                  << " | 任务: " << completed << "/" << totalTasks
                  << std::flush;
    };

    // 确保目标目录存在（加入异常处理）
    try
    {
        fs::create_directories(dst);
    }
    catch (const std::exception &e)
    {
        std::cerr << "创建目标目录失败: " << dst << " - " << e.what() << std::endl;
        return;
    }

    for (const auto &entry : fs::directory_iterator(src))
    {
        auto target = dst / entry.path().filename();

        if (fs::is_directory(entry))
        {
            futures.push_back(std::async(std::launch::async, [=, &directoriesCopied, &tasksCompleted, &copyErrors, &errorMutex]
                                         {
                                             try
                                             {
                                                 // 尝试创建子目录
                                                 fs::create_directories(target);
                                                 // 递归复制（可能抛出异常）
                                                 fs::copy(entry, target, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
                                                 directoriesCopied++;
                                             }
                                             catch (const std::exception &e)
                                             {
                                                 std::lock_guard<std::mutex> lock(errorMutex);
                                                 std::cerr << "\n目录复制错误: " << entry.path() << " -> " << target
                                                           << " - " << e.what() << std::endl;
                                                 copyErrors++;
                                             }
                                             tasksCompleted++; // 无论成功失败都标记任务完成
                                         }));
        }
        else if (fs::is_regular_file(entry))
        {
            futures.push_back(std::async(std::launch::async, [=, &filesCopied, &tasksCompleted, &copyErrors, &errorMutex]
                                         {
                                             try
                                             {
                                                 fs::copy_file(entry, target, fs::copy_options::overwrite_existing);
                                                 filesCopied++;
                                             }
                                             catch (const std::exception &e)
                                             {
                                                 std::lock_guard<std::mutex> lock(errorMutex);
                                                 std::cerr << "\n文件复制错误: " << entry.path() << " -> " << target
                                                           << " - " << e.what() << std::endl;
                                                 copyErrors++;
                                             }
                                             tasksCompleted++; // 无论成功失败都标记任务完成
                                         }));
        }
    }

    std::cout << "开始复制，总任务数: " << futures.size() << "\n";

    // 修改循环条件：基于tasksCompleted而非成功计数
    while (tasksCompleted < static_cast<int>(futures.size()))
    {
        showProgress();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    showProgress();
    std::cout << "\n复制完成! ";

    // 处理异步任务中的异常（防止未捕获异常传播）
    for (auto &f : futures)
    {
        try
        {
            f.get(); // 获取异步结果（可能重新抛出异常）
        }
        catch (const std::exception &e)
        {
            // 此处异常已在任务内处理过，此处仅确保不会终止程序
        }
    }

    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "总耗时: " << duration.count() / 1000.0 << " 秒 | 错误总数: " << copyErrors << "\n";
}
void createCMakeLists(const fs::path &parent_path, const string &projectName)
{
    // 修正路径：在项目目录下创建文件
    fs::path filePath = parent_path / "CMakeLists.txt";
    std::ofstream cmakeFile(filePath);

    if (!cmakeFile.is_open())
    {
        std::cerr << "Error: 无法在" << filePath << "下创建CMakeLists.txt 文件\n";
        return;
    }
    cmakeFile << "project(" << projectName << ")\n\n";
    cmakeFile << "include_directories(\n\t${CMAKE_CURRENT_SOURCE_DIR}/include\n)\n\n";
    cmakeFile << "file(GLOB SOURCES \"src/*.cpp\")\n\n";
    cmakeFile << "add_executable(${PROJECT_NAME} ${SOURCES})\n\n";
    cmakeFile << "set_target_properties(${PROJECT_NAME} PROPERTIES\n"
              << "\tOUTPUT_NAME \"${PROJECT_NAME}\"\n"
              << "\tRUNTIME_OUTPUT_DIRECTORY \"${CMAKE_BINARY_DIR}/${PROJECT_NAME}\"\n"
              << ")\n";
    cmakeFile.close();
}

void createReadme(const fs::path &parent_path, const string &projectName)
{
    fs::path filePath = parent_path / "readme.md";
    std::ofstream readme(filePath);

    if (!readme.is_open())
    {
        std::cerr << "Error: 无法在" << filePath << "下创建CMakeLists.txt 文件\n";
        return;
    }
    readme << "# " << projectName << "\n\n";
    readme << "## 简介\n\n";
    readme << "## 需求\n\n";
    readme << "## 练习\n";
    readme.close();
}

int main()
{
    std::cout << "=========================================\n";
    std::cout << "\t    新项目创建工具\n";
    std::cout << "=========================================\n\n";
    cout << "请输入要创建的项目名称:";
    getline(cin, projectName);
    cout << "\n检查项目名称是否合法..." << endl;

    if (!nameCheck(projectName))
    {
        cout << "项目名称不合法，请重新输入" << endl;
        cin.get();
        return 0;
    }
    cout << "项目名称合法" << endl;
    cout << "定位路径..." << endl;
    fs::path currentPath = fs::current_path();
    auto targetFolder = "CplusAlgo";
    auto targetPath = findAimFolder(currentPath, targetFolder, false, true);
    cout << "目标路径:" << *targetPath << endl;

    // 修改变量名避免重定义
    auto templateFolder = "000-CreateNewProject";
    auto templatePath = findAimFolder(currentPath, templateFolder, false, true);
    templatePath = *templatePath / "template";
    cout << "模板路径:" << *templatePath << endl;

    // 项目路径
    auto projectPath = *targetPath / projectName;
    cout << "项目路径:" << projectPath << endl;

    cout << "路径定位成功" << endl;

    cout << "创建文件夹..." << endl;
    if (!createFolder(*targetPath, projectName))
    {
        cout << "创建文件夹失败" << endl;
        cin.get();
        return 0;
    }
    cout << "文件夹创建成功" << endl;

    cout << "复制文件..." << endl;
    copyFiles(*templatePath, projectPath);
    cout << "创建CMakeLists.txt..." << endl;
    createCMakeLists(projectPath, projectName);
    cout << "创建readme.md..." << endl;
    createReadme(projectPath, projectName);
    cout << "项目创建完成!!!\n"
         << endl
         << "(=^._.^=)∫ 喵呜~\n"
         << endl
         << "点击任意键关闭程序..." << endl;

    cin.get();
    return 0;
}
