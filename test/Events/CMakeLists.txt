cmake_minimum_required(VERSION 3.30)

SET(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-O2 -g -Wall -Wextra -pedantic")

find_package(Boost REQUIRED COMPONENTS system)

add_executable(EventsTests Main.cpp 
    EventLoopTest.cpp)
target_link_libraries(EventsTests PRIVATE Core Events)
target_include_directories(EventsTests PRIVATE "src/Core" "src/Events")

add_test(NAME EventsTests COMMAND EventsTests --show_progress=yes)