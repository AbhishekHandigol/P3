cmake_minimum_required(VERSION 3.13)
project(P3)

set(CMAKE_CXX_STANDARD 14)

add_executable(P3 createheapoperationdata.cxx createteamdata.cxx createteams.cxx buildheap.cxx priorityqueue.cpp priorityqueue.h teamdata.cpp teamdata.h json.hpp)