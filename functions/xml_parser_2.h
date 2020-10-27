//
// Created by Nospy on 27/10/2020.
//

#ifndef CXML_XML_PARSER_2_H
#define CXML_XML_PARSER_2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "log.h"

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

typedef struct xml_document_s xml_document;
typedef struct xml_node_s xml_node;
typedef struct xml_attribute_s xml_attribute;
typedef struct xml_attribute_list_s xml_attribute_list;

struct xml_attribute_s {
    char *key;
    char *value;
};

struct xml_attribute_list_s {
    int capacity;
    int size;
    xml_attribute *data;
};

struct xml_node_s {
    char *tag;
    char *inner_text;
    xml_node *parent;
    xml_attribute_list attribute_list;
};

struct xml_document_s {
    char *source;
    xml_node *root_node;
};


int xml_document_load(xml_document *document, const char *path);

void xml_document_free(xml_document *document);

xml_node *xml_node_new(xml_node *parent);

void xml_node_free(xml_node *node);

xml_attribute *xml_attribute_new(xml_attribute *jesaispas);

void xml_attribute_free(xml_attribute *attribute);

void xml_attribute_list_init(xml_attribute_list *attribute_list);

void xml_attribute_list_add(xml_attribute_list *attribute_list, xml_attribute *attribute);

#endif //CXML_XML_PARSER_2_H
