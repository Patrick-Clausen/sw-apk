cmake_minimum_required(VERSION 3.20)
project(stl_algorithms)

set(CMAKE_CXX_STANDARD 14)

FILE(COPY product.db DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(stl_algorithms main.cpp)

