//
// Created by Unknow on 24/10/2020.
//

#ifndef CXML_LOG_H

#define gtk_app

#define CXML_LOG_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef gtk_app
#include "gtkFunctions.h"
#endif

int setLogFileName(char *filename);

void logIt(char *message, int error);

#endif //CXML_LOG_H
