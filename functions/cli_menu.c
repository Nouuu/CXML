//
// Created by Unknow on 18/11/2020.
//

#include "cli_menu.h"

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

    printf("Testing '");
    change_console_color(blue);
    printf("%s", trimmed_file_path);
    reset_console_color();
    printf("' file extension... Should be '");
    change_console_color(green);
    printf("%s", extension);
    reset_console_color();
    printf("'\n");

    sprintf(menu_message, "Testing '%s' file extension, should be '%s'", trimmed_file_path, extension);
    logIt(menu_message, 1);

    if (trimmed_file_path == NULL) {
        return 0;
    }
    char *bname = basename(trimmed_file_path);
    char *verif = strrchr(bname, '.');

    if (!verif || verif == bname) {
        change_console_color(red);
        printf("File '%s' don't have extension !\n\n", bname);
        sprintf(menu_message, "File '%s' don't have extension !\n", bname);
        logIt(menu_message, 1);
        reset_console_color();
        return 0;
    }

    int return_code = !strcmp(verif + 1, extension);
    if (!return_code) {
        change_console_color(red);
        printf("Wrong file extension, expected '%s' but founded '%s' !\n\n", extension, (verif + 1));
        sprintf(menu_message, "Wrong file extension, expected '%s' but founded '%s' !\n", extension, (verif + 1));
        logIt(menu_message, 1);
        reset_console_color();
    } else {
        change_console_color(green);
        printf("Extension is valid !\n\n");
        sprintf(menu_message, "Extension is valid !\n");
        logIt(menu_message, 1);
        reset_console_color();
    }
    return return_code;
}

int file_exist(char *trimmed_file_path) {
    if (!trimmed_file_path) {
        return 0;
    }

    printf("Testing if '");
    change_console_color(blue);
    printf("%s", trimmed_file_path);
    reset_console_color();
    printf("' exists...\n");

    sprintf(menu_message, "Testing if '%s' exists...\n", trimmed_file_path);
    logIt(menu_message, 1);


    FILE *fp = fopen(trimmed_file_path, "r");
    if (!fp) {
        change_console_color(red);
        printf("File don't exist !\n\n");
        sprintf(menu_message, "File don't exist !\n");
        logIt(menu_message, 1);

        reset_console_color();
        return 0;
    }

    change_console_color(green);
    printf("File exists !\n\n");
    sprintf(menu_message, "File exist !\n");
    logIt(menu_message, 1);
    reset_console_color();

    fclose(fp);
    return 1;
}
