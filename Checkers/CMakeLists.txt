cmake_minimum_required(VERSION 3.17)
project(Checkers C)

set(CMAKE_C_STANDARD 99)

add_executable(Checkers checkers_main.c checkers_functions.c checkers.h)