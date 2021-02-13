cmake_minimum_required(VERSION 3.0.2)
SET(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_STANDARD 98)

project(move-statements)
include(CheckIncludeFile)

file(GLOB PRJ_SOURCES ./src/*.cpp ./src/*.h )
add_executable(move-statements ${PRJ_SOURCES} )

target_include_directories( move-statements PUBLIC ./src )
target_link_libraries(move-statements pthread )

#target_compile_options(move-statements PRIVATE -fno-elide-constructors)

