//
// Created by Unknow on 24/10/2020.
//

#include "xml.h"

void readXML(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *xml_str = malloc(sizeof(char) * (size + 1));
    fread(xml_str, sizeof(char), size, fp);
    char *tag = "classroom";

    size_t end_pos = 0;
    char *between = getBetween(xml_str, tag, &end_pos);
    printf("XML between balise \"%s\" is :\n%s\n", tag, between);
    printf("Après:\n%s", xml_str + end_pos);
    free(xml_str);
    free(between);
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