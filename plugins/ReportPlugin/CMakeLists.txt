cmake_minimum_required(VERSION 3.16)

project(ReportPlugin LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

add_library(ReportPlugin SHARED
  src/reportplugin.cpp
  src/reportplugin.h
  src/reportdialog.h src/reportdialog.cpp src/reportdialog.ui
)

target_link_libraries(ReportPlugin PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
  common
)

# 设置include路径
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/common/infra/src/plugin
    ${CMAKE_SOURCE_DIR}/common/infra/src/patient
    ${CMAKE_CURRENT_BINARY_DIR}
)

# 设置插件属性
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_DIR}
)

# 如果是Windows，设置.dll输出到plugins目录
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_DIR}
        RUNTIME_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_DIR}
    )
endif()
