#this is CMake

cmake_minimum_required(VERSION 3.4)
project(CPP_A11_VEC3F)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp vec3f.cpp test11.cpp
        ../A1-2/main.cpp
        ../A1-3/main.cpp
        ../A3/main.cpp)
add_executable(vec3f ${SOURCE_FILES}
        ../A1-2/main.cpp
        ../A1-3/main.cpp)