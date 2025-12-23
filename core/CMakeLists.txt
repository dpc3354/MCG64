cmake_minimum_required(VERSION 3.19)
project(Core LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql)
find_package(Qt6 REQUIRED COMPONENTS Core Sql)

qt_add_executable(Core
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
)

target_link_libraries(Core
    PRIVATE
    Qt::Core
    Qt::Widgets
    Qt::Sql
    common
)

target_compile_definitions(Core PRIVATE
    PLUGIN_DIR="${PLUGIN_OUTPUT_DIR}"
)

# 设置include路径
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_CURRENT_BINARY_DIR}
)

include(GNUInstallDirs)

install(TARGETS Core
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

