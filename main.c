#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions/log.h"

char *logFile = "log.txt";

void initLogFile();

int main(int argc, char **argv) {
    initLogFile();


    return 0;
}

void initLogFile() {
    if (setLogFileName(logFile)) {
        //Erreur, impossible d'avoir un fichier de log correct
        fprintf(stderr, "Error! log file not set\nPress any key to close program\n");
        getchar();
        exit(1);
    }
}