cmake_minimum_required(VERSION 3.16.3)
project(CXML C)

set(CMAKE_C_STANDARD 99)

add_executable(CXML main.c functions/log.c functions/xml.c functions/xml_parser.c)