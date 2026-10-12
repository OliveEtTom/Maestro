cmake_minimum_required(VERSION 3.30)
project(Maestro)

SET(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-O2 -g -Wall -Wextra -pedantic")

add_subdirectory(src/Network)
add_subdirectory(src/Core)
add_subdirectory(test/Core)