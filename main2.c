//
// Created by audre on 15/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <ctype.h>
#include "functions/str_tools.h"
#include "functions/cli_menu.h"

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