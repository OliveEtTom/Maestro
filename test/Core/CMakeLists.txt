cmake_minimum_required(VERSION 3.30)

enable_testing()

SET(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-O2 -g -Wall -Wextra -pedantic")

find_package(Boost REQUIRED COMPONENTS system)

add_executable(CoreTests Main.cpp 
    ArrayTest.cpp 
    Latin1StringTest.cpp)
target_link_libraries(CoreTests PRIVATE Core)
target_include_directories(CoreTests PRIVATE "src/Core")

add_test(NAME CoreTests COMMAND CoreTests --show_progress=yes)