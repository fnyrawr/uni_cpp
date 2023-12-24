#this is CMake

cmake_minimum_required(VERSION 3.4)
project(CPP_A13_VEC)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp test13.cpp)
add_executable(vec ${SOURCE_FILES})