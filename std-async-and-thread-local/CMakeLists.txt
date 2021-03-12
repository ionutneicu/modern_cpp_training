cmake_minimum_required(VERSION 3.0.2)
SET(CMAKE_BUILD_TYPE Debug)
project(std-async-and-thread-local)
include(CheckIncludeFile)

file(GLOB PRJ_SOURCES ./src/*.cpp ./src/*.h )

add_executable(std-async-and-thread-local ${PRJ_SOURCES} )
target_include_directories( std-async-and-thread-local PUBLIC ./src )
target_link_libraries(std-async-and-thread-local pthread )


# Locate GTest
#find_package(GTest REQUIRED)
#target_include_directories(${GTEST_INCLUDE_DIRS} ${PRJ_SOURCES})
# Link runTests with what we want to test and the GTest and pthread library
#add_executable(runTests ${tests_SRC})
#target_link_libraries(runTests ivo ${GTEST_LIBRARIES} pthread )

