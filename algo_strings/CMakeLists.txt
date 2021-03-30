cmake_minimum_required(VERSION 3.0.2)
SET(CMAKE_BUILD_TYPE Debug)
project(algo_strings)
include(CheckIncludeFile)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
file(GLOB PRJ_SOURCES ./src/*.cpp ./src/*.h )

add_executable(algo_strings ${PRJ_SOURCES} )
target_include_directories( algo_strings PUBLIC ./src )
target_link_libraries(algo_strings pthread )


# Locate GTest
#find_package(GTest REQUIRED)
#target_include_directories(${GTEST_INCLUDE_DIRS} ${PRJ_SOURCES})
# Link runTests with what we want to test and the GTest and pthread library
#add_executable(runTests ${tests_SRC})
#target_link_libraries(runTests ivo ${GTEST_LIBRARIES} pthread )

