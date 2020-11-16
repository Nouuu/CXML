//
// Created by audre on 15/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <ctype.h>

int menu(char **xmlpath, char **dtdpath);

int getPath(char **path);

int verif_xml(char *xml_file);

int verif_dtd(char *dtd_file);

int endFunc(int code, char *buffer);

char *trimwhitespace(char *str);

int main(int argc, char **argv) {
    if (argc == 3) {
        printf("%s", argv[1]);
        printf("%s", argv[2]);
    } else {
//        argv = menu();
        menu((char **)argv[1], (char **)argv[2]);
    }

    printf("%s", *argv);
    return 0;
}

int menu(char **xmlpath, char **dtdpath) {

    char *buffer = malloc(sizeof(char) * 255 * 255 + 1);

// https://www.dummies.com/programming/c/how-to-use-the-fgets-function-for-text-input-in-c-programming/
// https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
// https://linux.die.net/man/3/fgets

    printf("You did not put files in args so please provide it: \n");
    do {
        printf("Enter dtd path :\n");
        fflush(stdin);
        fgets(buffer, 255, stdin);
        buffer = strtok(buffer, "\n");
        *dtdpath = buffer;
        getPath(dtdpath);
    } while (!verif_dtd(*dtdpath));

    do {
        printf("Enter xml path :\n");
        fflush(stdin);
        fgets(buffer, 255, stdin);
        buffer = strtok(buffer, "\n");
        *xmlpath = buffer;
        getPath(xmlpath);
    } while (!verif_xml(*xmlpath));

    return 1;
}

int verif_dtd(char *dtd_file) {
    if (dtd_file == NULL) {
        return 0;
    }
    char *bname = basename(dtd_file);
    char *verif = strrchr(bname, '.');
    if (!verif || verif == bname) {
        return 0;
    }
    //ta chaine de base est pas bonne donc forcément
    // Cad ? A cause du scanf ?

    return strcmp(verif + 1, "dtd") == 0;
}

int verif_xml(char *xml_file) {
    if (xml_file == NULL) {
        return 0;
    }
    char *bname = basename(xml_file);
    char *verif = strrchr(bname, '.');
    if (!verif || verif == bname) {
        return 0;
    }
    strcmp(verif + 1, "xml") == 0;
}

int getPath(char **path) {
    char *buff = malloc(sizeof(char) * 255 * 255 + 1);
    char *tmp;

    printf("Enter directory path :\n");
    fflush(stdin);
    fflush(stdout);
    if (fgets(buff, 255 * 255, stdin) == NULL) {
        return endFunc(1, buff);
    }
    if (buff[0] == '\n') {
        return endFunc(1, buff);
    }

    buff = strtok(buff, "\n");

    tmp = trimwhitespace(buff);

    if (strlen(tmp) == 0) {
        return endFunc(1, buff);
    }

    *path = malloc(sizeof(char) * (strlen(tmp) + 1));
    strcpy(*path, tmp);
    free(buff);

    printf("Path: |%s|\n", *path);
    return 0;
}

char *trimwhitespace(char *str) {
    char *end;
    // Trim leading space
    while (isspace((unsigned char) *str)) str++;

    if (*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

int endFunc(int code, char *buffer) {
    if (buffer != NULL) {
        free(buffer);
    }
    return code;
}