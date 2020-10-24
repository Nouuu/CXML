//
// Created by Unknow on 24/10/2020.
//

#include "log.h"

char *logFileName = NULL;

int setLogFileName(char *filename) {
    if (!strlen(filename)) {
        return 1;
    }
    if (logFileName != NULL) {
        free(logFileName);
    }
    logFileName = malloc(sizeof(char) * (strlen(filename) + 1));
    strcpy(logFileName, filename);
    return 0;
}


void logIt(char *message) {
    char buff[20];
    struct tm *sTm;
    FILE *fp = fopen(logFileName, "a+");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open log file !\n");
        return;
    }
    if (!strlen(message)) {
        fprintf(stderr, "Message empty\n");
        return;
    }

    time_t now = time(0);
    sTm = gmtime(&now);
    strftime(buff, sizeof(buff), "%d-%m-%Y %H:%M:%S", sTm);

    printf("[%s] %s\n", buff, message);
    fprintf(fp, "[%s] %s\n", buff, message);
    fclose(fp);
}
