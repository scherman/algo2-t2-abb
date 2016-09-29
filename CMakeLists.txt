cmake_minimum_required(VERSION 3.5)
project(algo2_t3_abb)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES tests.cpp)
add_executable(algo2_t3_abb ${SOURCE_FILES})