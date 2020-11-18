//
// Created by Unknow on 18/11/2020.
//

#ifndef CXML_CONSOLE_COLOR_H
#define CXML_CONSOLE_COLOR_H

#include <stdio.h>

#if defined(_WIN32)

#include <windows.h>

enum console_color {
    red = 12,
    green = 10,
    blue = 9,
};
#elif __unix__

enum console_color {
    red = 1,
    green = 2,
    blue = 5,
};

#endif

void change_console_color(enum console_color color);

void reset_console_color();

#endif //CXML_CONSOLE_COLOR_H
