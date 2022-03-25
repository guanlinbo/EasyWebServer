cmake_minimum_required(VERSION 3.14.5)
project(untitled)

set(CMAKE_CXX_STANDARD 11)
find_package(Threads)
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -pthread")
add_executable(untitled main.cpp EasyTcpServer.cpp EasyTcpServer.h)
