//
// Created by audre on 15/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <ctype.h>
#include "functions/str_tools.h"

int menu(char **xml_path, char **dtd_path);

int verif_file_extension(char *trimmed_file_path, const char *extension);

int file_exist(char *trimmed_file_path);

int check_file_exist_and_extension(char *trimmed_file_path, const char *extension);

char *get_user_input_trimmed_file_path();

int main(int argc, char **argv) {
    char *xml_file_path = NULL;
    char *dtd_file_path = NULL;

    if (argc == 3) {
        printf("Given arguments\n");
        printf("\txml : %s\n", argv[1]);
        printf("\tdtd : %s\n", argv[2]);
        xml_file_path = strdup(argv[1]);
        dtd_file_path = strdup(argv[2]);
    }

    menu(&xml_file_path, &dtd_file_path);

    printf("Here should be final and valid path :\n");
    printf("\txml : %s\n", xml_file_path);
    printf("\tdtd : %s\n", dtd_file_path);

    free(xml_file_path);
    free(dtd_file_path);
    return 0;
}

int menu(char **xml_path, char **dtd_path) {

    char *temp = *xml_path;
    *xml_path = strtrim_space(*xml_path);
    if (temp) {
        free(temp);
    }
    temp = *dtd_path;
    *dtd_path = strtrim_space(*dtd_path);
    if (temp) {
        free(temp);
    }

    while (!check_file_exist_and_extension(*xml_path, "xml")) {
        printf("Please enter xml file path (relative or absolute) :\n");
        if (*xml_path) {
            free(*xml_path);
        }
        *xml_path = get_user_input_trimmed_file_path();
    }

    while (!check_file_exist_and_extension(*dtd_path, "dtd")) {
        printf("Please enter dtd file path (relative or absolute) :\n");
        if (*dtd_path) {
            free(*dtd_path);
        }
        *dtd_path = get_user_input_trimmed_file_path();
    }

    return 1;
}

char *get_user_input_trimmed_file_path() {
    char *buffer = calloc(sizeof(char), 501);

    fflush(stdin);
    fgets(buffer, 500, stdin);

    //remove end '\n' from user input
    char *return_char = strchr(buffer, '\n');
    if (return_char) {
        *return_char = '\0';
    } else {
        buffer[500] = '\0';
    }

    char *trimmed_string = strtrim_space(buffer);
    free(buffer);
    return trimmed_string;
}

int check_file_exist_and_extension(char *trimmed_file_path, const char *extension) {
    return verif_file_extension(trimmed_file_path, extension)
           && file_exist(trimmed_file_path);
}

int verif_file_extension(char *trimmed_file_path, const char *extension) {
    if (!trimmed_file_path) {
        return 0;
    }

    printf("Testing '%s' file extension... Should be '%s'\n", trimmed_file_path, extension);
    if (trimmed_file_path == NULL) {
        return 0;
    }
    char *bname = basename(trimmed_file_path);
    char *verif = strrchr(bname, '.');

    if (!verif || verif == bname) {
        printf("File '%s' don't have extension !\n", bname);
        return 0;
    }

    int return_code = !strcmp(verif + 1, extension);
    if (!return_code) {
        printf("Wrong file extension, expected '%s' but founded '%s' !\n", extension, (verif + 1));
    }
    return return_code;
}

int file_exist(char *trimmed_file_path) {
    if (!trimmed_file_path) {
        return 0;
    }

    printf("Testing if '%s' exists...\n", trimmed_file_path);

    FILE *fp_dtd = fopen(trimmed_file_path, "r");
    if (!fp_dtd) {
        printf("File don't exist !\n");
        return 0;
    }
    printf("File exists !\n");
    fclose(fp_dtd);
    return 1;
}

