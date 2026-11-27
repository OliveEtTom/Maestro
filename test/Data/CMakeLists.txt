cmake_minimum_required(VERSION 3.30)

SET(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-O2 -g -Wall -Wextra -pedantic")

find_package(Boost REQUIRED COMPONENTS system)

add_executable(DataTests Main.cpp 
    NeuralNetworkTest.cpp)
target_link_libraries(DataTests PRIVATE Core Data)
target_include_directories(DataTests PRIVATE "src/Core" "src/Data")

add_test(NAME DataTests COMMAND DataTests --show_progress=yes)