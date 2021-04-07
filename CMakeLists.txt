cmake_minimum_required(VERSION 3.17)
project(engine C)

set(CMAKE_C_STANDARD 99)

add_executable(engine main.c board.h board.c)