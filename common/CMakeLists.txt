cmake_minimum_required(VERSION 3.16)

project(common LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Sql)

add_library(common SHARED
  infra/src/plugin/IPlugin.h
  infra/src/plugin/pluginmanager.h infra/src/plugin/pluginmanager.cpp
  infra/src/patient/patientlistform.h infra/src/patient/patientlistform.cpp infra/src/patient/patientlistform.ui
  infra/src/database/databasemanager.h infra/src/database/databasemanager.cpp
  infra/src/database/baserepository.h infra/src/database/baserepository.cpp
  infra/src/models/user.h infra/src/models/user.cpp
  infra/src/repositories/userrepository.h infra/src/repositories/userrepository.cpp
  infra/src/models/patient.h infra/src/models/patient.cpp
  infra/src/repositories/patientrepository.h infra/src/repositories/patientrepository.cpp
)

target_link_libraries(common PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Sql
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_compile_definitions(common PRIVATE COMMON_LIBRARY)


install(TARGETS common
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
