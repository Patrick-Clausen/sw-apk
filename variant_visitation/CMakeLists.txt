cmake_minimum_required(VERSION 3.20)
project(variant_visitation)

set(CMAKE_CXX_STANDARD 17)

include_directories(C:/local/boost_1_77_0)
LINK_DIRECTORIES(C:/local/boost_1_77_0/libs)
#TARGET_LINK_LIBRARIES(C:/local/boost_1_77_0/libs)

add_executable(variant_visitation main.cpp)
