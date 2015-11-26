cmake_minimum_required(VERSION 3.3)
project(system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")

link_libraries(m)

set(SOURCE_FILES main.c)
add_executable(system ${SOURCE_FILES} data.c set.c operation.c cJSON.c cJSON.h)
