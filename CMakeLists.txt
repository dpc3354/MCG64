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
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/plugins)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(MCG64
    WIN32 MACOSX_BUNDLE
    core/src/main.cpp
    core/src/mainwindow.cpp
    core/src/mainwindow.h
    core/src/mainwindow.ui
    infra/src/plugin/IPlugin.h
    infra/src/plugin/pluginmanager.h infra/src/plugin/pluginmanager.cpp
)

target_link_libraries(MCG64
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_link_libraries(MCG64 PRIVATE Qt6::Core)

# 设置include路径
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# 编译插件
add_subdirectory(plugins/PatientsPlugin)
add_subdirectory(plugins/AnalysisPlugin)

include(GNUInstallDirs)

install(TARGETS MCG64
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET MCG64
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
