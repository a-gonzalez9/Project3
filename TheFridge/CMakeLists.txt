cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(TheFridge)

set(SFML_DIR "C:/Users/14078/Desktop/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

add_executable(TheFridge main.cpp
        hashmap.cpp
        hashmap.h
        heap.cpp
        heap.h)

target_link_libraries(TheFridge sfml-system sfml-window sfml-graphics sfml-audio)