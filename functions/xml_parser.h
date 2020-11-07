//
// Created by Nospy on 27/10/2020.
//

#ifndef CXML_XML_PARSER_H
#define CXML_XML_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "log.h"
#include "str_tools.h"

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
typedef struct xml_node_list_s xml_node_list;
typedef enum tag_type_e tag_type;

struct xml_attribute_s {
    char *key;
    char *value;
};

struct xml_attribute_list_s {
    int capacity;
    int size;
    xml_attribute *data;
};

struct xml_node_list_s {
    int capacity;
    int size;
    xml_node **data;
};

struct xml_node_s {
    char *tag;
    char *inner_text;
    xml_node *parent;
    xml_attribute_list attribute_list;
    xml_node_list children;
};


struct xml_document_s {
    char *source;
    char *version;
    char *encoding;
    xml_node *root_node;
};

enum tag_type_e {
    START_TAG,
    INLINE_TAG
};

char *xml_node_attribute_value(xml_node *node, const char *key);

xml_attribute *xml_node_attribute(xml_node *node, const char *key);

int ends_with(const char *str, const char *end_str);

int xml_document_load(xml_document *document, const char *path);

tag_type parse_attributes(const char *source, int *i, char *parsing_buffer, int *parsing_buffer_i,
                          xml_node *current_node, size_t size);

void xml_attribute_free(xml_attribute *attribute);

void xml_attribute_list_add(xml_attribute_list *attribute_list, xml_attribute *attribute);

void xml_attribute_list_init(xml_attribute_list *attribute_list);

void xml_document_free(xml_document *document);

void xml_node_free(xml_node *node);

void xml_node_list_add(xml_node_list *node_list, xml_node *node);

void xml_node_list_free(xml_node_list *node_list);

void xml_node_list_init(xml_node_list *node_list);

xml_node *xml_node_child(xml_node *parent, int index);

xml_node *xml_node_get(xml_node_list node_list, int index);

xml_node *xml_node_new(xml_node *parent);

xml_node_list *xml_node_children_by_tagname(xml_node *parent, const char *tag);

int string_only_contain_space_characters(const char *string);

char *strcat_realloc(char *str_1, char *str_2);

#endif //CXML_XML_PARSER_H