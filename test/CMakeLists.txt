cmake_minimum_required(VERSION 3.8)
project(rfkill_test)

include_directories(../src)

link_libraries(rfkill)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES test.cpp)
add_executable(rfkill_test ${SOURCE_FILES})