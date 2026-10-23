cmake_minimum_required(VERSION 3.30)

SET(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-O2 -g -Wall -Wextra -pedantic")

find_package(Boost REQUIRED COMPONENTS system)

add_library(Network SHARED 
    TcpClient.cpp TcpServer.cpp IpAddress.cpp)
target_include_directories(Network PUBLIC .)

add_executable(Server server.cpp) 
add_executable(Client client.cpp) 
target_compile_options(Server PRIVATE -fPIC)
target_compile_options(Client PRIVATE -fPIC)
target_link_libraries(Server PRIVATE Boost::system Network)
target_include_directories(Server PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(Client PRIVATE Boost::system Network)
target_include_directories(Client PRIVATE ${Boost_INCLUDE_DIRS})