//
// Created by Unknow on 18/11/2020.
//

#include "console_color.h"

void change_console_color(enum console_color color) {
#ifdef __unix__
    printf("\033[0;3%dm", color);
#elif defined(_WIN32)
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, color);
#endif

}

void reset_console_color() {
#ifdef __unix__
    printf("\033[0m");
#elif defined(_WIN32)
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, 15);
#endif

}