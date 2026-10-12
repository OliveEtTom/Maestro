cmake_minimum_required(VERSION 3.13)
add_library(Core SHARED 
    Latin1String.cpp)
target_include_directories(Core PUBLIC .)