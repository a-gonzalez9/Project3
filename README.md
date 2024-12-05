
To run this application, you need the following:

C++ Compiler: A compiler that supports C++17 or later

SFML Library: SFML version 2.5.1 or later installed on your system

CMake: For building the project


Installation and Setup

Clone the Repository:

git clone <repository_url>
cd TheFridge

CMake Configuration:
Ensure you have a CMakeLists.txt file configured to include SFML:

cmake_minimum_required(VERSION 3.10)
project(TheFridge)
set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
add_executable(TheFridge main.cpp)
target_link_libraries(TheFridge sfml-system sfml-window sfml-graphics sfml-audio)

Build the Project:

mkdir build
cd build
cmake ..
make

Run the Application:

./TheFridge
