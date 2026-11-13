cmake_minimum_required(VERSION 3.13)
add_library(Events SHARED 
    EventLoop.cpp)
target_include_directories(Events PUBLIC .)
target_link_libraries(Events PRIVATE Core)
target_include_directories(Events PRIVATE "src/Core")