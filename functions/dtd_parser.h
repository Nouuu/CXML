//
// Created by Unknow on 24/10/2020.
//

#ifndef CXML_XML_H
#define CXML_XML_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "log.h"


// Structure
typedef struct dtd_node_s dtd_node;
typedef struct dtd_document_s dtd_document;


struct dtd_node_s {
    char *tag_name;
    char *name;
    char *rule;
    struct dtd_node_s *next;
};

struct dtd_document_s {
    char *source;
    char *root_node;
    dtd_node *first_node;
};

char *get_dtd_document_source(char *path);

dtd_node *get_data(dtd_node *list, int i);

int parse_dtd(dtd_document *document, dtd_node *list);

dtd_node *init_linked_list();

void add_data_at_end(dtd_node **list, dtd_node *new_node);


#endif //CXML_XML_H
