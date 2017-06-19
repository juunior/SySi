cmake_minimum_required(VERSION 3.5)
project(Sysi5)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Wall -pedantic")

add_executable(sigtest2C sigtest2C.c)
add_executable(sigtest sigtest.c)
add_executable(start start.c)
add_executable(sem sem.c)
add_executable(sigtest2 sigtest2.c)