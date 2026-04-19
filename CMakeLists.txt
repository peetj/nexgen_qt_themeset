cmake_minimum_required(VERSION 3.21)
project(nexgen_qt_themeset VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_library(nexgen_qt_themeset STATIC)
add_library(nexgen::qt_themeset ALIAS nexgen_qt_themeset)

target_sources(nexgen_qt_themeset
  PRIVATE
    src/ThemeManager.cpp
  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
      include/nexgen/themes/ThemeManager.h
      include/nexgen/themes/ThemeTypes.h
)

target_link_libraries(nexgen_qt_themeset PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets)

target_include_directories(nexgen_qt_themeset PUBLIC include)

# For consumers via add_subdirectory()
