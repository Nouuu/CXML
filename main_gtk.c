//
// Created by Unknow on 20/11/2020.
//



#include "gtkFunctions.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __unix__
char *logFile = "log.txt";
#elif defined(__WIN32) || defined(WIN32)
char *logFile = "C:\\ProgramData\\cxml_log.txt";
#endif
char *gladeFile = "gtk_files/window.glade";
App_widgets *widgets;


void initLogFile();

int main(int argc, char **argv) {
    initLogFile();
    startGTK(&argc, &argv, gladeFile);

    return 42;
}

void initLogFile() {
    if (setLogFileName(logFile)) {
        //Erreur, impossible d'avoir un fichier de log correct
        fprintf(stderr, "Error! log file not set\nPress any key to close program\n");
        getchar();
        exit(1);
    }
}