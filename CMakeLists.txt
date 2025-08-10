cmake_minimum_required(VERSION 3.31)
project(linear_sort)

set(CMAKE_CXX_STANDARD 23)

add_executable(linear_sort main.cpp
        sorting.cpp
        sorting.h)

target_link_libraries(linear_sort PRIVATE stdc++exp)
