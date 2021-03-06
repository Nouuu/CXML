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

static int line;
static int column;

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
    INLINE_TAG,
    ERROR_PARSING
};

void inc_column(int count, const char *source, int i);

void newline();

char *strcat_realloc(char *str_1, char *str_2);

char *xml_node_attribute_value(xml_node *node, const char *key);

int ends_with(const char *str, const char *end_str);

int string_only_contain_space_characters(const char *string);

int xml_document_load(xml_document *document, const char *path);

tag_type
parse_attributes(const char *source, int *i, char *parsing_buffer, int *parsing_buffer_i, xml_node *current_node,
                 size_t size);

int index_out_of_range(int i, int size);

int parse_xml_file(xml_document *document, size_t size);

int parse_xml_carret_open(xml_document *document, int *i, int *parsing_buffer_i, xml_node **current_node,
                          char *parsing_buffer, char *message_buffer, size_t size);

int parse_xml_inner_text(int *parsing_buffer_i, char *parsing_buffer, xml_node **current_node, char *message_buffer);

int parse_xml_ending_node(xml_document *document, int *i, int *parsing_buffer_i, char *parsing_buffer,
                          xml_node **current_node, char *message_buffer, int size);

int parse_xml_comment(xml_document *document, int *i, int *parsing_buffer_i, char *parsing_buffer,
                      char *message_buffer, int size);

int parse_xml_doctype(xml_document *document, int *i, int *parsing_buffer_i, char *parsing_buffer, int size);

int valid_tag_name(const char *tag);

void reset_parsing_buffer(char *parsing_buffer, int *parsing_buffer_i);

void xml_attribute_free(xml_attribute *attribute);

void xml_attribute_list_add(xml_attribute_list *attribute_list, xml_attribute *attribute);

void xml_attribute_list_init(xml_attribute_list *attribute_list);

void xml_document_free(xml_document *document);

void xml_node_free(xml_node *node);

void xml_node_list_add(xml_node_list *node_list, xml_node *node);

void xml_node_list_free(xml_node_list *node_list);

void xml_node_list_init(xml_node_list *node_list);

xml_attribute *xml_node_attribute(xml_node *node, const char *key);

xml_node *xml_node_child(xml_node *parent, int index);

xml_node *xml_node_get(xml_node_list node_list, int index);

xml_node *xml_node_new(xml_node *parent);

xml_node_list *xml_node_children_by_tagname(xml_node *parent, const char *tag);

#endif //CXML_XML_PARSER_H
