# 设置最低 CMake 版本要求
cmake_minimum_required(VERSION 3.10)

# 创建排序算法项目
project(000-CreateNewProject)

# 复制模板文件
# add_custom_target(CopyTemplate ALL
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_CURRENT_SOURCE_DIR}/template
#         ${CMAKE_CURRENT_BINARY_DIR}/template
#     COMMENT "Copying template files..."
# )

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置exe输出格式为GBK 解决中文乱码问题
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fexec-charset=GBK")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK")

# 设置构建类型（Debug/Release）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
    # set(CMAKE_BUILD_TYPE Release)
endif()

# 添加包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 收集所有源文件
file(GLOB SOURCES "src/*.cpp")

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 使可执行文件依赖复制操作
# add_dependencies(${PROJECT_NAME} CopyTemplate)

# 设置目标属性
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}"
)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

