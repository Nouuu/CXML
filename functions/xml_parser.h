//
// Created by Nospy on 26/10/2020.
//

#ifndef CXML_XML_PARSER_H
#define CXML_XML_PARSER_H

#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "log.h"

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

typedef unsigned char uint8_t;
typedef enum bool bool;
typedef enum xml_parser_offset xml_parser_offset;
typedef struct xml_buffer xml_buffer;
typedef struct xml_attribute xml_attribute;
typedef struct xml_node xml_node;
typedef struct xml_document xml_document;
typedef struct xml_parser xml_parser;

enum xml_parser_offset {
    NO_CHARACTER = -1,
    CURRENT_CHARACTER = 0,
    NEXT_CHARACTER = 1,
};

enum bool {
    false = 0,
    true = 1
};


struct xml_buffer {
    char *buffer;
//    size_t length;
};

struct xml_attribute {
    char *name;
    char *content;
};

struct xml_node {
    char *name;
    char *content;
    xml_attribute **attributes;
    xml_node **children;
};

struct xml_document {
    xml_buffer buffer;
    xml_node *root;
};

struct xml_parser {
    char *buffer;
    size_t position;
//    size_t length;
};

char *xml_node_attribute_content(xml_node *node, size_t attribute);

char *xml_node_attribute_name(xml_node *node, size_t attribute);

char *xml_node_content(xml_node *node);

char *xml_node_name(xml_node *node);

char *xml_string_clone(char *s);

size_t get_zero_terminated_array_attributes(xml_attribute **attributes);

size_t get_zero_terminated_array_nodes(xml_node **nodes);

size_t xml_node_attributes(xml_node *node);

size_t xml_node_children(xml_node *node);

void xml_attribute_free(xml_attribute *attribute);

void xml_document_free(xml_document *document, bool free_buffer);

void xml_node_free(xml_node *node);

void xml_parser_error(xml_parser *parser, xml_parser_offset offset, char const *message);

xml_document *xml_open_document(FILE *source);

xml_document *xml_parse_document(uint8_t *buffer, size_t length);

xml_node *xml_document_root(xml_document *document);

xml_node *xml_easy_child(xml_node *node, uint8_t const *child, ...);

xml_node *xml_node_child(xml_node *node, size_t child);

#endif //CXML_XML_PARSER_H
