cmake_minimum_required(VERSION 3.0.2)
SET(CMAKE_BUILD_TYPE Debug)
project(auto-tests)
include(CheckIncludeFile)

file(GLOB PRJ_SOURCES ./src/*.cpp ./src/*.h )

add_executable(auto-tests ${PRJ_SOURCES} )
target_include_directories( auto-tests PUBLIC ./src )
target_include_directories( auto-tests PUBLIC ../include )
target_link_libraries(auto-tests pthread )


# Locate GTest
#find_package(GTest REQUIRED)
#target_include_directories(${GTEST_INCLUDE_DIRS} ${PRJ_SOURCES})
# Link runTests with what we want to test and the GTest and pthread library
#add_executable(runTests ${tests_SRC})
#target_link_libraries(runTests ivo ${GTEST_LIBRARIES} pthread )

