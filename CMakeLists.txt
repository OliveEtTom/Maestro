cmake_minimum_required(VERSION 3.30)
project(Maestro)

enable_testing()

SET(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-O2 -g -Wall -Wextra -pedantic")

find_package(Boost REQUIRED COMPONENTS system)

add_executable(Server src/Network/server.cpp) 
add_executable(Client src/Network/client.cpp src/Network/TcpClient.cpp src/Network/IpAddress.cpp) 
target_compile_options(Server PRIVATE -fPIC)
target_compile_options(Client PRIVATE -fPIC)
target_link_libraries(Server PRIVATE Boost::system)
target_include_directories(Server PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(Client PRIVATE Boost::system)
target_include_directories(Client PRIVATE ${Boost_INCLUDE_DIRS})

add_subdirectory(src/Core)
add_executable(CoreTests 
    test/Core/Main.cpp 
    test/Core/ArrayTest.cpp 
    test/Core/Latin1StringTest.cpp)
target_link_libraries(CoreTests PRIVATE Core)
target_include_directories(CoreTests PRIVATE "src/Core")

add_test(NAME CoreTests COMMAND CoreTests --show_progress=yes)