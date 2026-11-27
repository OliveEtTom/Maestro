cmake_minimum_required(VERSION 3.13)
add_library(Data SHARED 
    BinaryCrossEntropy.cpp
    NeuralNetwork.cpp)
target_include_directories(Data PUBLIC .)
target_link_libraries(Data PRIVATE Core)
target_include_directories(Data PRIVATE "src/Core")