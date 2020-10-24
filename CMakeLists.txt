# cmake_minimum_required(VERSION <specify CMake version here>)
project(CXML C)

set(CMAKE_C_STANDARD 99)

add_executable(CXML main.c functions/log.c)