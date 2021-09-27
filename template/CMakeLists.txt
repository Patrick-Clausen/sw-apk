cmake_minimum_required(VERSION 3.20)
project(template)

set(CMAKE_CXX_STANDARD 14)

add_executable(template main.cpp MyArray.h MyArray_ptr.h)
