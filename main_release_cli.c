//
// Created by Unknow on 15/11/2020.
//
#include "dtd_validation.h"
#include "console_color.h"
#include "cli_menu.h"
#include "log.h"


char *logFile = "log.txt";

void initLogFile();


int main(int argc, char **argv) {
    reset_console_color();
    initLogFile();

    char *xml_file_path = NULL;
    char *dtd_file_path = NULL;

    change_console_color(blue);
    printf("===========================================\n||");
    change_console_color(green);
    printf(" WELCOME TO XML DTD VALIDATION PROGRAM ");
    change_console_color(blue);
    printf("||\n===========================================\n\n");
    reset_console_color();

    printf("You can call the program directly in command line with this syntax :\n./");
    change_console_color(green);
    printf("program_executable ");
    change_console_color(blue);
    printf("xml_file_path ");
    change_console_color(red);
    printf("dtd_file_path\n");
    reset_console_color();
    printf("Path can be relative or absolute\n\n");

    if (argc == 3) {

        printf("Given arguments\n");
        printf("\txml : '%s'\n", argv[1]);
        printf("\tdtd : '%s'\n\n", argv[2]);
        xml_file_path = strdup(argv[1]);
        dtd_file_path = strdup(argv[2]);
    }

    menu(&xml_file_path, &dtd_file_path);

    printf("\nHere should be final and valid path we are hoing to work on :\n");
    printf("\txml : '");
    change_console_color(green);
    printf("%s", xml_file_path);
    reset_console_color();
    printf("'\n\tdtd : '");
    change_console_color(green);
    printf("%s", dtd_file_path);
    reset_console_color();
    printf("'\n\n");

    change_console_color(red);
    int return_code = validate_dtd(xml_file_path, dtd_file_path);

    free(xml_file_path);
    free(dtd_file_path);

    if (return_code) {
        change_console_color(green);
        printf("\nYour xml document is conform to given dtd !\n");
    } else {
        change_console_color(red);
        printf("\nYour xml document is not conform to given dtd !\n");
    }

    reset_console_color();

    printf("\nPress any key to leave\n");
    getchar();

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
