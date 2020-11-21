//
// Created by Unknow on 24/10/2020.
//


#ifndef CXML_LOG_H
#define CXML_LOG_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//#include "gtkFunctions.h"

int setLogFileName(char *filename);

void logIt(char *message, int error);

void console_writeline(const char *text);
#endif //CXML_LOG_H
