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
typedef struct dtd_rule_s dtd_rule;
typedef struct dtd_attribute_s dtd_attribute;

struct dtd_node_s {
    char *tag_name;
    char *rule_type;
    dtd_rule *rule;
    dtd_attribute *attribute;
    struct dtd_node_s *next;
};

struct dtd_rule_s {
    char *rule_name;
    char rule_spec;
    char rule_sep;
    struct dtd_rule_s *next;
};

struct dtd_document_s {
    char *source;
    char *root_node;
    dtd_node *element_node;
    dtd_attribute *attribute_node;
};

struct dtd_attribute_s{
    char *element_name;
    char *attribute_name;
    char *attribute_type;
    char *attribute_value;
    struct dtd_attribute_s *next;
};

int dtd_document_load(dtd_document *document, const char *path);

char *get_dtd_document_source(const char *path);

dtd_node *get_data(dtd_node *list, int i);

int parse_dtd(dtd_document *document);

dtd_attribute *init_dtd_attribute();

void add_dtd_node_attribute_at_end(dtd_attribute **list, dtd_attribute *new_node);

dtd_node *init_dtd_node();

void add_dtd_element_node_at_end(dtd_node **list, dtd_node *new_node);

dtd_rule *init_dtd_rule();

void add_dtd_rule_at_end(dtd_rule **list, dtd_rule *new_rule);

void foward_spaces(char **current_char, size_t *current_i);

int is_special(char c);

int is_delim(char c);

int is_node_spec(char c);
#endif //CXML_XML_H
