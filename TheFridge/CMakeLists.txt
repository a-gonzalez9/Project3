cmake_minimum_required(VERSION 3.27)
project(TheFridge)

set(CMAKE_CXX_STANDARD 17)

add_executable(TheFridge main.cpp
        hashmap.cpp
        hashmap.h
        heap.cpp
        heap.h)
