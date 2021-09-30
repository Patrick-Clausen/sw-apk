cmake_minimum_required(VERSION 3.20)
project(boost_timercallback)

set(CMAKE_CXX_STANDARD 17)

add_executable(boost_timercallback Bindfunction.cpp Events.cpp Timer.cpp)
