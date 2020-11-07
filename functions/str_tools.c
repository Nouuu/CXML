//
// Created by Unknow on 07/11/2020.
//

#include "str_tools.h"

char *strltrim(const char *str, char c) {
    char *trim = NULL;
    size_t i, len;

    if (str == NULL) {
        return trim;
    }

    len = strlen(str);
    if (len <= 0) {
        return trim;
    }

    /*
    i = 0;
    while (i < len && str[i] == c) {
        i++;
    }
    */

    for (i = 0; i < len && str[i] == c; i++);

    if (i == len) {
        return NULL;
    }

    trim = malloc(sizeof(char) * (len - i + 1));

    strcpy(trim, str + i);

    return trim;
}

char *strrtrim(const char *str, char c) {
    char *trim = NULL;
    size_t i, len;

    if (str == NULL) {
        return trim;
    }

    len = strlen(str);
    if (len <= 0) {
        return trim;
    }

    for (i = len; i > 0 && str[i - 1] == c; i--);

    if (i == 0) {
        return trim;
    }

    trim = malloc(sizeof(char) * (i + 1));

    strncpy(trim, str, i);
    trim[i] = '\0';

    return trim;
}

char *strtrim(const char *str, char c) {
    char *ltrim = NULL;
    char *lrtrim = NULL;

    ltrim = strltrim(str, c);

    lrtrim = strrtrim(ltrim, c);

    if (ltrim != NULL) {
        free(ltrim);
    }
    return lrtrim;
}

char *strltrim_space(const char *str) {
    char *trim = NULL;
    size_t i, len;

    if (str == NULL) {
        return trim;
    }

    len = strlen(str);
    if (len <= 0) {
        return trim;
    }

    /*
    i = 0;
    while (i < len && str[i] == c) {
        i++;
    }
    */

    for (i = 0; i < len && isspace(str[i]); i++);

    if (i == len) {
        return NULL;
    }

    trim = malloc(sizeof(char) * (len - i + 1));

    strcpy(trim, str + i);

    return trim;
}

char *strrtrim_space(const char *str) {
    char *trim = NULL;
    size_t i, len;

    if (str == NULL) {
        return trim;
    }

    len = strlen(str);
    if (len <= 0) {
        return trim;
    }

    for (i = len; i > 0 && isspace(str[i - 1]); i--);

    if (i == 0) {
        return trim;
    }

    trim = malloc(sizeof(char) * (i + 1));

    strncpy(trim, str, i);
    trim[i] = '\0';

    return trim;
}

char *strtrim_space(const char *str) {
    char *ltrim = NULL;
    char *lrtrim = NULL;

    ltrim = strltrim_space(str);

    lrtrim = strrtrim_space(ltrim);

    if (ltrim != NULL) {
        free(ltrim);
    }
    return lrtrim;
}