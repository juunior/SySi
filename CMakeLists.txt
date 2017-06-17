cmake_minimum_required(VERSION 3.5)
project(Sysi5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu99 -Wall -pedantic")


add_executable(start start.c)
