cmake_minimum_required(VERSION 3.10)

project(server2)

add_executable(server main.cpp server.cpp) 

target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})