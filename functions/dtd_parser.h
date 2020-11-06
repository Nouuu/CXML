//
// Created by Unknow on 24/10/2020.
//

#ifndef CXML_XML_H
#define CXML_XML_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"


// Structure
typedef struct linked_list_s linked_list;

struct linked_list_s {
    char *data;
    struct linked_list_s *previous;
    struct linked_list_s *next;
};
linked_list *init_linked_list(char *data);
void add_data_at_end(linked_list *list, char *data);
linked_list *get_data(linked_list *list, int i);

char *dtd_to_string(char *path);
linked_list *get_dtd_rules(char *buf);


void readXML(FILE *fp);

void readDTD(FILE *dtd_file, FILE *xml_file);

char *getBetween(char *xml_str, char *tag, size_t *end_pos);

char *getRootTag(char *xml_str);

char *getFileStr(FILE *fp);

void checkRootTag(char *dtd_str, char *xml_str);



#endif //CXML_XML_H
