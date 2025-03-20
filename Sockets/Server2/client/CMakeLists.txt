cmake_minimum_required(VERSION 3.10)

project(server2)

add_executable(client main.cpp client.cpp) 

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})