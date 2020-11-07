//
// Created by Unknow on 07/11/2020.
//

#ifndef CXML_STR_TOOLS_H
#define CXML_STR_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * Trim left side of the string with specific character
 * @param str string to trim
 * @param c character to use in trim
 * @return new trimmed string
 * @return NULL if string or trimmed string is empty
 */
char *strltrim(const char *str, char c);

/**
 * Trim right side of the string with specific character
 * @param str string to trim
 * @param c character to use in trim
 * @return new trimmed string
 * @return NULL if string or trimmed string is empty
 */
char *strrtrim(const char *str, char c);

/**
 * Trim both left and right side of the string with specific character
 * @param str string to trim
 * @param c character to use in trim
 * @return new trimmed string
 * @return NULL if string or trimmed string is empty
 */
char *strtrim(const char *str, char c);

/**
 * Trim left side of the string with all kind of space character (' ', '\ n', '\ t', '\ v', '\ f', '\ r')
 * @param str
 * @return new trimmed string
 * @return NULL if string or trimmed string is empty
 */
char *strltrim_space(const char *str);

/**
 * Trim right side of the string with all kind of space character (' ', '\ n', '\ t', '\ v', '\ f', '\ r')
 * @param str
 * @return new trimmed string
 * @return NULL if string or trimmed string is empty
 */
char *strrtrim_space(const char *str);

/**
 * Trim both left and right side of the string with all kind of space character (' ', '\ n', '\ t', '\ v', '\ f', '\ r')
 * @param str
 * @return new trimmed string
 * @return NULL if string or trimmed string is empty
 */
char *strtrim_space(const char *str);

#endif //CXML_STR_TOOLS_H
