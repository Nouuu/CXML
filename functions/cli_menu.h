//
// Created by Unknow on 18/11/2020.
//

#ifndef CXML_CLI_MENU_H
#define CXML_CLI_MENU_H

#include "str_tools.h"
#include "console_color.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <ctype.h>

int menu(char **xml_path, char **dtd_path);

int verif_file_extension(char *trimmed_file_path, const char *extension);

int file_exist(char *trimmed_file_path);

int check_file_exist_and_extension(char *trimmed_file_path, const char *extension);

char *get_user_input_trimmed_file_path();


#endif //CXML_CLI_MENU_H
