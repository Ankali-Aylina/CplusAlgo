cmake_minimum_required( VERSION 3.10)

project(002-RabbitSequence)

# 添加包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 收集所有源文件
file(GLOB SOURCES "src/*.cpp")

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 设置目标属性
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}"
)
