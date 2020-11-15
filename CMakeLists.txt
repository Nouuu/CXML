cmake_minimum_required(VERSION 3.16.3)
project(CXML C)

set(CMAKE_C_STANDARD 99)

add_executable(CXML main.c
        functions/log.c
        functions/dtd_parser.c
        functions/dtd_rules.c
        functions/xml_parser.c
        functions/xml_finder.c
        tests/xml_parsing_test.c
        functions/str_tools.c
        functions/dtd_validation.c)