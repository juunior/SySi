cmake_minimum_required(VERSION 3.5)
project(Sysi5)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Wall -pedantic")


add_executable(start start.c)
