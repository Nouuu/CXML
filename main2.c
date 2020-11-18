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

int verif_file_extension(char *file_path, const char *extension);

int file_exist(char *file_path);

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

    while (!menu(&xml_file_path, &dtd_file_path));

    printf("Here should be final and valid path :\n");
    printf("\txml : %s\n", xml_file_path);
    printf("\tdtd : %s\n", dtd_file_path);
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
    } while (!verif_file_extension(buffer, "dtd"));

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
/*

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

*/
    return 1;
}

int verif_file_extension(char *trimmed_file_path, const char *extension) {
    printf("Tesing '%' extension... Should be '%s'", trimmed_file_path, extension);
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

char *get_user_input_trimmed_file_path() {
    return 0;
}