cmake_minimum_required(VERSION 3.16.3)
project(CXML C)

set(CMAKE_C_STANDARD 99)

set(PROJECT_NAME CXML)
set(CLI_APP_VERSION 1.8)
set(GTK_APP_VERSION 1.7)

set(CLI_APP_NAME ${PROJECT_NAME}_CLI_${CLI_APP_VERSION})
set(GTK_APP_NAME ${PROJECT_NAME}_GTK_${GTK_APP_VERSION})

set(required_files
        functions/log.c
        functions/dtd_parser.c
        functions/dtd_rules.c
        functions/xml_parser.c
        functions/xml_finder.c
        functions/str_tools.c
        functions/console_color.c
        functions/cli_menu.c
        functions/dtd_validation.c)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS} functions dtd_files xml_files)
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

if (UNIX)
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,-export-dynamic")
endif (UNIX)


add_executable(${CLI_APP_NAME}
        main_release_cli.c
        ${required_files})

set(GTK_EXECUTABLE_NAME CXML_GTK_V1.7)

add_executable(${GTK_APP_NAME}
        main_gtk.c
        functions/gtkFunctions.c
        ${required_files})

target_link_libraries(${GTK_APP_NAME} ${GTK3_LIBRARIES})