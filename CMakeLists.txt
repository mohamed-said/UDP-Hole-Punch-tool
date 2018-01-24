cmake_minimum_required(VERSION 3.0)
project(udp_holepunch_tool)

find_package(Threads)

set(CMAKE_CXX_STANDARD 11)

add_executable(udp_holepunch_tool
        UDPSocket.cpp
        UDPSocket.h
        HolePunchEngine.cpp
        HolePunchEngine.h
        main.cpp)

target_link_libraries(udp_holepunch_tool ${CMAKE_THREAD_LIBS_INIT})
