//
// Created by Nospy on 27/10/2020.
//

#ifndef CXML_XML_PARSER_2_H
#define CXML_XML_PARSER_2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

typedef struct xml_document_s xml_document;
typedef struct xml_node_s xml_node;

struct xml_document_s {
    char *source;
    xml_node *root_node;
};

struct xml_node_s {
    char *tag;
    char *inner_text;
    xml_node *parent;
};


int xml_document_load(xml_document *document, const char *path);

void xml_document_free(xml_document *document);

xml_node *xml_node_new(xml_node *parent);

void xml_node_free(xml_node *node);

#endif //CXML_XML_PARSER_2_H
