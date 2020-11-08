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
    char *tag_name;
    char *name;
    char *rule;
    struct linked_list_s *previous;
    struct linked_list_s *next;
};

char *dtd_to_string(char *path);

linked_list *get_data(linked_list *list, int i);

linked_list *get_dtd_rules(char *buf);

linked_list *init_linked_list(char *data);

void add_data_at_end(linked_list *list, char *data);

void parse_line_elements(linked_list *linkedList, const char *data);


#endif //CXML_XML_H
