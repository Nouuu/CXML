//
// Created by Unknow on 15/11/2020.
//
#include "dtd_validation.h"
#include "log.h"


#if defined(_WIN32)

#include <windows.h>

enum console_color {
    red = 12,
    green = 10,
    blue = 9,
};
#elif __unix__

enum console_color {
    red = 1,
    green = 2,
    blue = 5,
};

#endif

void change_console_color(enum console_color color);

void reset_console_color();

char *logFile = "log.txt";

void initLogFile();


int main(int argc, char **argv) {
    reset_console_color();
    initLogFile();
    printf("Welcome to xml dtd validation program\n");
    if (argc == 3) {
        printf("We are going to validate '");
        change_console_color(blue);
        printf("%s", argv[1]);
        reset_console_color();
        printf("' xml document\nwith '");
        change_console_color(blue);
        printf("%s", argv[2]);
        reset_console_color();
        printf("' dtd document\n\n");


        change_console_color(red);
        int return_code = validate_dtd(argv[1], argv[2]);

        if (return_code) {
            change_console_color(green);
            printf("\nYour xml document is conform to given dtd !\n");
        } else {
            change_console_color(red);
            printf("\nYour xml document is not conform to given dtd !\n");
        }
    } else {
        change_console_color(red);
        printf("Wrong number of arugments!\n");
        reset_console_color();
        printf("Expected 2, got %d\n", argc - 1);
        printf("You have to call the program with this syntax :\n./");
        change_console_color(green);
        printf("program_executable ");
        change_console_color(blue);
        printf("xml_file_path ");
        change_console_color(red);
        printf("dtd_file_path\n");
        reset_console_color();
        printf("Path can be relative or absolute\n");
    }
    reset_console_color();

    printf("\nPress any key to leave\n");
    getchar();

    return 0;
}

void change_console_color(enum console_color color) {
#ifdef __unix__
    printf("\033[0;3%dm", color);
#elif defined(_WIN32)
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, color);
#endif

}

void reset_console_color() {
#ifdef __unix__
    printf("\033[0m");
#elif defined(_WIN32)
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, 15);
#endif

}

void initLogFile() {
    if (setLogFileName(logFile)) {
        //Erreur, impossible d'avoir un fichier de log correct
        fprintf(stderr, "Error! log file not set\nPress any key to close program\n");
        getchar();
        exit(1);
    }
}
