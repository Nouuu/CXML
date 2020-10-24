#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions/log.h"

char *logFile = "log.txt";

void initLogFile();

FILE *openXMLFile(int argc, char **argv);

int main(int argc, char **argv) {
    initLogFile();
    FILE *xml_file = openXMLFile(argc, argv);


    fclose(xml_file);
    return 0;
}

FILE *openXMLFile(int argc, char **argv) {
    FILE *fp = NULL;
    char message[255];
    if (argc == 2) {
        sprintf(message, "Open XML File : %s...", argv[1]);
        logIt(message);

        fp = fopen(argv[1], "r");

        if (fp == NULL) {
            logIt("File not found !");
            exit(1);
        } else {
            logIt("File opened");
        }
    } else {
        logIt("Wrong arg number");
        exit(1);
    }
    return fp;
}

void initLogFile() {
    if (setLogFileName(logFile)) {
        //Erreur, impossible d'avoir un fichier de log correct
        fprintf(stderr, "Error! log file not set\nPress any key to close program\n");
        getchar();
        exit(1);
    }
}