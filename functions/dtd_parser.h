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
typedef struct element_node_s element_node;
typedef struct dtd_document_s dtd_document;
typedef struct dtd_rule_s dtd_rule;
typedef struct attribute_node_s attribute_node;

struct dtd_document_s {
    char *source;
    char *root_node;
    element_node *first_element_node;
    attribute_node *first_attribute_node;
};

struct element_node_s {
    char *tag_name;
    char *rule_type;
    dtd_rule *rule;
    struct element_node_s *next;
};

struct dtd_rule_s {
    char *rule_name;
    char rule_spec;
    char rule_sep;
    struct dtd_rule_s *next;
};

struct attribute_node_s {
    char *rule_type;
    char *element_name;
    char *attribute_name;
    char *attribute_type;
    char *attribute_option;
    struct attribute_node_s *next;
};

int carret_open(dtd_document **document, size_t size, size_t *current_i, char **current_char);

int element_node_parse(dtd_document **document, size_t size, size_t *current_i, char **current_char);

int attribut_node_parse(dtd_document **document, size_t size, size_t *current_i, char **current_char);

int doctype_process(dtd_document **document, size_t size);

int no_doctype_process(dtd_document **document, size_t size);

int is_doctype(dtd_document *document, size_t size);

char *get_doctype(size_t size, size_t *current_i, char **current_char);

int dtd_document_load(dtd_document *document, const char *path);

char *get_dtd_document_source(const char *path);

element_node *get_data(element_node *list, int i);

int parse_dtd(dtd_document *document);

attribute_node *init_dtd_attribute();

void add_dtd_node_attribute_at_end(attribute_node **list, attribute_node *new_node);

element_node *init_dtd_node();

void add_dtd_element_node_at_end(element_node **list, element_node *new_node);

dtd_rule *init_dtd_rule();

void add_dtd_rule_at_end(dtd_rule **list, dtd_rule *new_rule);

void foward_spaces(char **current_char, size_t *current_i);

int is_special(char c);

int is_delim(char c);

int is_node_spec(char c);

#endif //CXML_XML_H
