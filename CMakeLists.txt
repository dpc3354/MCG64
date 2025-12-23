cmake_minimum_required(VERSION 3.19)
project(MCG64 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置Qt相关选项
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 插件输出到专门目录
set(PLUGIN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/plugins)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

add_subdirectory(common)
add_subdirectory(core)
add_subdirectory(plugins)
