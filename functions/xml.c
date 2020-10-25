//
// Created by Unknow on 24/10/2020.
//

#include "xml.h"

void readXML(FILE *fp) {
    char *xml_str = getFileStr(fp);
    char *tag = "classroom";

    size_t end_pos = 0;
    char *between = getBetween(xml_str, tag, &end_pos);

    if (between != NULL) {
//        printf("XML between balise \"%s\" is :\n%s\n", tag, between);
        free(between);
    }

    char *root_tag = getRootTag(xml_str);
    if (root_tag != NULL) {
        printf("Root tag is : |%s|\n", root_tag);
    }

    free(root_tag);
    free(xml_str);
}

void readDTD(FILE *dtd_file, FILE *xml_file) {
    char message[255] = {0};
    char *dtd_str = getFileStr(dtd_file);
    char *xml_str = getFileStr(xml_file);

    checkRootTag(dtd_str, xml_str);
    
    free(dtd_str);
    free(xml_str);
    free(xml_file);
}

void checkRootTag(char *dtd_str, char *xml_str) {
    char message[255] = {0};
    char dtd_root_tag[255] = {0};
    sscanf(dtd_str, "<!DOCTYPE %[^ ]", dtd_root_tag);

    if (strlen(dtd_root_tag) <= 0) {
        logIt("Wrong dtd root tag !");
        exit(1);
    }

    printf("DOCTYPE ROOT TAG : |%s|\n", dtd_root_tag);

    char *xml_root_tag = getRootTag(xml_str);
    if (xml_root_tag == NULL) {
        logIt("Wrong xml root tag !");
        exit(1);
    }

    if (strcmp(dtd_root_tag, xml_root_tag) != 0) {
        sprintf(message, "Wrong root tag. Expected |%s|, got |%s|", dtd_root_tag, xml_root_tag);
        logIt(message);
        exit(1);
    } else {
        sprintf(message, "Good root tag : |%s|", dtd_root_tag);
        logIt(message);
    }
    free(xml_root_tag);
}

char *getFileStr(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (size == 0) {
        return NULL;
    }

    char *file_str = malloc(sizeof(char) * (size + 1));
    fread(file_str, sizeof(char), size, fp);

    return file_str;
}


char *getRootTag(char *xml_str) {
    char buff[255] = {0};
    size_t cursor = 0;
    sscanf(xml_str, "<?xml%[^\n]", buff);

    if (strlen(buff) <= 0) {
        logIt("Can't find xml tag");
        return NULL;
    }
    cursor += 5 + strlen(buff) + 1;

    while ((xml_str + cursor)[0] == '\r') {
        cursor += 2;
    }

    sscanf(xml_str + cursor, "<%[^>]", buff);
    if (strlen(buff) <= 0) {
        logIt("Can't find root tag");
        return NULL;
    }

    char *result = malloc(sizeof(char) * (strlen(buff) + 1));
    strcpy(result, buff);

    return result;
}


/**
 * Récupère dans une chaine de caractère allouée, le contenu XML entre un tag donné
 * @param xml_str   le contenu du fichier xml
 * @param tag       le tag
 * @param end_pos   contient la position juste après le tag trouvé
 * @return la chaine de caractère contenant le XML entre le tag donné (la première occurence).
 * @return Si le tag n'est pas trouvé, renvoie NULL
 */
char *getBetween(char *xml_str, char *tag, size_t *end_pos) {
    size_t len, pos;
    char message[100] = {0};
    char *begin_tag = NULL;
    char *end_tag = NULL;
    char *begin_tag_pos = NULL;
    char *end_tag_pos = NULL;

    len = strlen(xml_str);
    if (len <= 0) {
        logIt("looking for empty tag!");
        return NULL;
    }
    begin_tag = malloc(sizeof(char) * (len + 3));
    sprintf(begin_tag, "<%s>", tag);
    end_tag = malloc(sizeof(char) * (len + 4));
    sprintf(end_tag, "</%s>", tag);

    begin_tag_pos = strstr(xml_str, begin_tag);
    if (begin_tag_pos == NULL) {
        sprintf(message, "Cannot find %s tag", begin_tag);
        logIt(message);
        return NULL;
    }

    end_tag_pos = strstr(xml_str, end_tag);
    if (end_tag_pos == NULL || end_tag_pos < begin_tag_pos) {
        sprintf(message, "Cannot find %s tag", end_tag);
        logIt(message);
        return NULL;
    }

    len = end_tag_pos - begin_tag_pos - strlen(begin_tag);
    pos = begin_tag_pos - xml_str + strlen(begin_tag);

    char *response = malloc(sizeof(char) * (len + 1));
    strncpy(response, xml_str + pos, len);
    response[len] = 0;

    *end_pos = end_tag_pos - xml_str + strlen(end_tag);
    return response;
}