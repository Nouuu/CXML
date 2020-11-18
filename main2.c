//
// Created by audre on 15/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <ctype.h>
#include "functions/str_tools.h"

int menu(char **xmlpath, char **dtdpath);

int verif_xml(char *xml_file);

int verif_dtd(char *dtd_file);

int endFunc(int code, char *buffer);

int main(int argc, char **argv) {
    if (argc == 3) {
        printf("%s", argv[1]);
        printf("%s", argv[2]);
    } else {
//        argv = menu();
        menu((char **) argv[1], (char **) argv[2]);
    }

    printf("%s", *argv);
    return 0;
}

int menu(char **xmlpath, char **dtdpath) {

    char *buffer = malloc(sizeof(char) * 256);

// https://www.dummies.com/programming/c/how-to-use-the-fgets-function-for-text-input-in-c-programming/
// https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
// https://linux.die.net/man/3/fgets

    printf("You did not put files in args so please provide it: \n");
    do {
        printf("Enter dtd path :\n");
        fflush(stdin);
        fgets(buffer, 255, stdin);
        char *return_char = strchr(buffer, '\n');
        if (return_char) {
            *return_char = '\0';
        } else {
            buffer[255] = '\0';
        }
    } while (!verif_dtd(buffer));

    char *trimmed_dtd_path = strtrim_space(buffer);

    FILE *fp_dtd = fopen(trimmed_dtd_path, "r");
    if (!fp_dtd) {
        printf("Le fichier dtd demandé n'existe pas !");
        return 0;
    }
    printf("Le fichier dtd demandé existe !");
    fclose(fp_dtd);

    // Segmentation Fault ici
    (*dtdpath) = trimmed_dtd_path;
    // --------------------------------------------------------------------------

    do {
        printf("Enter xml path :\n");
        fflush(stdin);
        fgets(buffer, 255, stdin);
        char *return_char = strchr(buffer, '\n');
        if (return_char) {
            *return_char = '\0';
        } else {
            buffer[255] = '\0';
        }
    } while (!verif_xml(buffer));

    char *trimmed_xml_path = strtrim_space(buffer);

    FILE *fp_xml = fopen(trimmed_xml_path, "r");
    if (!fp_xml) {
        printf("Le fichier xml demandé n'existe pas !");
        return 0;
    }
    printf("Le fichier xml demandé existe !");
    fclose(fp_xml);

    *xmlpath = trimmed_xml_path;

    return 1;
}

int verif_dtd(char *dtd_file) {
    if (dtd_file == NULL) {
        return 0;
    }
    char *trimmed = strltrim(dtd_file, '.');
    char *bname = basename(trimmed);
    char *verif = strrchr(bname, '.');
    if (!verif || verif == bname) {
        free(trimmed);
        printf("Wrong file extension !\n");
        return 0;
    }

    int return_code = !strcmp(verif + 1, "dtd");
    free(trimmed);
    if (!return_code) {
        printf("Wrong file extension !\n");
    }
    return return_code;
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

int endFunc(int code, char *buffer) {
    if (buffer != NULL) {
        free(buffer);
    }
    return code;
}