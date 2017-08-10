cmake_minimum_required(VERSION 3.8)
project(rfkill)

add_subdirectory(test)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES rfkill.cpp rfkill.h)
add_library(rfkill ${SOURCE_FILES})