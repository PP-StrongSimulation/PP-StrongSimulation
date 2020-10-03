# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.8)

# 项目信息
project (GraphIndex)

add_definitions(-std=c++17)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(GMP REQUIRED)
#include_directories("${GMP_INCLUDE_DIR}")

# 指定生成目标
add_executable(main ${DIR_SRCS})
target_link_libraries(main -lgmp)
