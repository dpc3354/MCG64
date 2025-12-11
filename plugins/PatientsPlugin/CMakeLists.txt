cmake_minimum_required(VERSION 3.19)

project(PatientsPlugin)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置Qt相关选项
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 查找Qt
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

# 插件源文件
set(PLUGIN_SOURCES
    
)

set(PLUGIN_HEADERS
    
)

# 创建插件库
add_library(${PROJECT_NAME} SHARED
    ${PLUGIN_SOURCES}
    ${PLUGIN_HEADERS}
)

# 链接Qt库
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)

# 设置include路径
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/infra/plugin
)

# 设置插件属性
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/plugins
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/plugins
)

# 如果是Windows，设置.dll输出到plugins目录
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/plugins
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/plugins
    )
endif()
