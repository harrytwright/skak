cmake_minimum_required(VERSION 3.17)
project(skak C)

set(CMAKE_C_STANDARD 99)

add_executable(skak main.c board.h board.c bitboards.c bitboards.h defs.h assert.h init.c init.h)