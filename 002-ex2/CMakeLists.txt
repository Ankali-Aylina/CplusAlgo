# 设置最低CMake版本要求
cmake_minimum_required(VERSION 3.10)

#项目名称
project(002-ex2)

# 设置不同配置的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release/bin)

# 设置库文件目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release/lib)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 确保在Debug构建中生成调试信息
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# 添加包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 设置默认构建类型为Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()


# 收集所有源文件
file(GLOB SOURCES "src/*.cpp")

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 设置目标属性
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}"
)

# 为Release构建设置GBK字符集
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(MSVC)
        # MSVC编译器设置GBK字符集
        target_compile_options(${PROJECT_NAME} PRIVATE
            "/source-charset:.936"
            "/execution-charset:.936"
        )
        message(STATUS "Release构建配置: 使用MSVC编译器，已设置GBK字符集")
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        # GCC/Clang编译器设置GBK字符集
        target_compile_options(${PROJECT_NAME} PRIVATE
            "-fexec-charset=GBK"
            "-finput-charset=UTF-8"
        )
        message(STATUS "Release构建配置: 使用GCC/Clang编译器，已设置GBK字符集")
    else()
        message(WARNING "Release构建配置: 未知编译器，无法自动设置GBK字符集")
    endif()
endif()


        