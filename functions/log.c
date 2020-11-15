//
// Created by Unknow on 24/10/2020.
//

#include "log.h"

char *log_file_name = NULL;

int setLogFileName(char *filename) {
    if (!strlen(filename)) {
        return 1;
    }
    if (log_file_name != NULL) {
        free(log_file_name);
    }
    log_file_name = malloc(sizeof(char) * (strlen(filename) + 1));
    strcpy(log_file_name, filename);
    return 0;
}


void logIt(char *message, int error) {
    char buff[20];
    struct tm *s_tm;
    FILE *fp = fopen(log_file_name, "a+");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open log file !\n");
        return;
    }
    if (!strlen(message)) {
        fprintf(stderr, "Message empty\n");
        return;
    }

    time_t now = time(0);
    s_tm = gmtime(&now);
    strftime(buff, sizeof(buff), "%d-%m-%Y %H:%M:%S", s_tm);

    /*if (error) {
        fprintf(stderr, "[%s] %s\n", buff, message);
    } else {
        printf("[%s] %s\n", buff, message);
    }*/
    if (error) {
        printf("[%s] %s\n", buff, message);
    }
    fprintf(fp, "[%s] %s\n", buff, message);
    fclose(fp);
}
