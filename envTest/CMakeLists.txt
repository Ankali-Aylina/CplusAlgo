# 创建排序算法项目
project(envTest)

# 添加包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 收集所有源文件
file(GLOB SOURCES "src/*.cpp")

# 创建可执行文件
add_executable(envTest ${SOURCES})

# 设置目标属性
set_target_properties(envTest PROPERTIES
    OUTPUT_NAME "sorting"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/envTest
)
