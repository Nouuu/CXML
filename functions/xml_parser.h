//
// Created by Nospy on 26/10/2020.
//

#ifndef CXML_XML_PARSER_H
#define CXML_XML_PARSER_H

#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "log.h"

typedef unsigned char uint8_t;
typedef enum bool bool;
typedef struct xml_buffer xml_buffer;
typedef struct xml_string xml_string;
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
    uint8_t *buffer;
    size_t length;
};

struct xml_string {
    uint8_t const *buffer;
    size_t length;
};

struct xml_attribute {
    xml_string *name;
    xml_string *content;
};

struct xml_node {
    xml_string *name;
    xml_string *content;
    xml_attribute **attributes;
    xml_node **children;
};

struct xml_document {
    xml_buffer buffer;
    xml_node *root;
};

struct xml_parser {
    uint8_t *buffer;
    size_t position;
    size_t length;
};

xml_document *xml_parse_document(uint8_t *buffer, size_t length);

xml_document *xml_open_document(FILE *source);

void xml_document_free(xml_document *document, bool free_buffer);

xml_node *xml_document_root(xml_document *document);

xml_string *xml_node_name(xml_node *node);

xml_string *xml_node_content(xml_node *node);

size_t xml_node_children(xml_node *node);

xml_node *xml_node_child(xml_node *node, size_t child);

size_t xml_node_attributes(xml_node *node);

xml_string *xml_node_attribute_name(xml_node *node, size_t attribute);

xml_string *xml_node_attribute_content(xml_node *node, size_t attribute);

xml_node *xml_easy_child(xml_node *node, uint8_t const *child, ...);

size_t xml_string_length(xml_string *string);

void xml_string_copy(xml_string *string, uint8_t *buffer, size_t length);

size_t get_zero_terminated_array_attributes(xml_attribute **attributes);

size_t get_zero_terminated_array_nodes(xml_node **nodes);

bool xml_string_equals(xml_string *a, xml_string *b);

uint8_t *xml_string_clone(struct xml_string *s);

void xml_string_free(xml_string *string);

void xml_attribute_free(xml_attribute *attribute);

void xml_node_free(xml_node *node);


#endif //CXML_XML_PARSER_H
