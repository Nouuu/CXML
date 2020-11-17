//
// Created by Unknow on 24/10/2020.
//

#include "dtd_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

attribute_node *init_dtd_attribute() {
    attribute_node *attribute = malloc(sizeof(attribute_node));

    attribute->element_name = NULL;
    attribute->attribute_name = NULL;
    attribute->attribute_type = NULL;
    attribute->attribute_option = NULL;
    attribute->next = NULL;

    return attribute;
};

void add_dtd_node_attribute_at_end(attribute_node **list, attribute_node *new_node) {
    if (*list == NULL) {

        *list = new_node;

    } else {

        attribute_node *current_node = *list;
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = new_node;

    }
};

element_node *init_dtd_node() {

    element_node *linked_list_1 = malloc(sizeof(element_node));

    linked_list_1->next = NULL;
    linked_list_1->rule_type = NULL;
    linked_list_1->tag_name = NULL;
    linked_list_1->rule = NULL;

    return linked_list_1;
}

void add_dtd_element_node_at_end(element_node **list, element_node *new_node) {

    if (*list == NULL) {
        *list = new_node;
    } else {
        element_node *current_node = *list;
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = new_node;
    }
}

dtd_rule *init_dtd_rule() {

    dtd_rule *rule = malloc(sizeof(dtd_rule));

    rule->rule_name = NULL;
    rule->rule_sep = ' ';
    rule->rule_spec = ' ';
    rule->next = NULL;

    return rule;
}

void add_dtd_rule_at_end(dtd_rule **list, dtd_rule *new_rule) {

    if (*list == NULL) {

        *list = new_rule;

    } else {

        dtd_rule *current_rule = *list;
        while (current_rule->next != NULL) {
            current_rule = current_rule->next;
        }
        current_rule->next = new_rule;

    }
}

element_node *get_data(element_node *list, int i) {
    if (i < 0) {
        return NULL;
    }

    while (i > 0 && list != NULL) {
        list = list->next;
        i--;
    }

    return list;
}

int dtd_document_load(dtd_document *document, const char *path) {
    document->source = get_dtd_document_source(path);
    if (document->source == NULL) {
        return 0;
    }

    return parse_dtd(document);
}

char *get_dtd_document_source(const char *path) {
    char message[255] = {0};
    size_t size;
    FILE *fichier = NULL;
    fichier = fopen(path, "r");
    if (fichier == NULL) {
        sprintf(message, "DTD file '%s' not found !", path);
        logIt(message, 1);
        return NULL;
    }

    fseek(fichier, 0, SEEK_END);
    size = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);

    char *buf = calloc(size + 1, sizeof(char));
    fread(buf, sizeof(char), size, fichier);
    buf[size] = '\0';
    fclose(fichier);
    //logIt(buf);
    return buf;
}

int parse_dtd(dtd_document *document) {

    char parsing_buffer[255] = {0};
    char message_buffer[255] = {0};
    int parsing_buffer_i = 0;
    size_t size = strlen(document->source);

    char *current_char = document->source;
    size_t current_i = 0;

    //////////// FIND !DOCTYPE //////////////

    if (is_doctype(document, size)) {
        return doctype_process(&document, size);
    } else {
        return no_doctype_process(&document, size);
    }

    //////////// GO TO '[' //////////////
    return 0;
}

int is_doctype(dtd_document *document, size_t size) {
    char parsing_buffer[255] = {0};
    int parsing_buffer_i = 0;

    char *current_char = document->source;
    size_t current_i = 0;

    while (*current_char != '<' && current_i < size) {
        current_i++;
        current_char++;
    }

    if (current_i >= size) {
        return 0;
    }

    current_i++;
    current_char++;

    while (!isspace(*current_char) && current_i < size) {
        parsing_buffer[parsing_buffer_i] = *current_char;
        parsing_buffer_i++;
        current_i++;
        current_char++;
    }
    parsing_buffer[parsing_buffer_i] = '\0';

    if (!strcmp(parsing_buffer, "!DOCTYPE")) {
        return 1;
    }
    return 0;
}

char *get_doctype(size_t size, size_t *current_i, char **current_char) {
    char parsing_buffer[255] = {0};
    int parsing_buffer_i = 0;

    while (**current_char != '<' && (*current_i) < size) {
        (*current_i)++;
        (*current_char)++;
    }

    if ((*current_i) >= size) {
        return 0;
    }

    (*current_i)++;
    (*current_char)++;

    while (!isspace(*(*current_char)) && (*current_i) < size) {
        parsing_buffer[parsing_buffer_i] = *(*current_char);
        parsing_buffer_i++;
        (*current_i)++;
        (*current_char)++;
    }
    parsing_buffer[parsing_buffer_i] = '\0';
    foward_spaces(&(*current_char), &(*current_i));

    parsing_buffer_i = 0;
    while (!isspace(*(*current_char)) && *(*current_char) != '[') {
        parsing_buffer[parsing_buffer_i] = *(*current_char);
        parsing_buffer_i++;
        (*current_i)++;
        (*current_char)++;
    }
    parsing_buffer[parsing_buffer_i] = '\0';

    return strdup(parsing_buffer);
}

int doctype_process(dtd_document **document, size_t size) {

    char *current_char = (*document)->source;
    size_t current_i = 0;
    char message_buffer[255] = {0};

    (*document)->root_node = get_doctype(size, &current_i, &current_char);


    while (*current_char != '[') {
        if (!isspace(*current_char)) {
            if (*current_char == '>') {
                return 1;
            }
            logIt("DOCTYPE Node contain other things than juste root node name", 1);
            return 0;
        }
        current_i++;
        current_char++;
    }

    current_i++;
    current_char++;

    while (*current_char != ']' && current_i < size - 1) {

        //Start element node
        if (*current_char == '<') {
            if (!carret_open(document, size, &current_i, &current_char)) {
                return 0;
            }
        } else {
            current_char++;
            current_i++;
        }
        /*if (current_i >= size) {
            logIt("Can't find endind array carracter", 1);
            return 0;
        }*/
    }

    return 1;
}

int no_doctype_process(dtd_document **document, size_t size) {
    char *current_char = (*document)->source;
    size_t current_i = 0;

    while (current_i < size) {

        //Start element node
        if (*current_char == '<') {
            if (!carret_open(document, size, &current_i, &current_char)) {
                return 0;
            }
        } else {
            current_char++;
            current_i++;
        }
    }
    return 1;
}

int carret_open(dtd_document **document, size_t size, size_t *current_i, char **current_char) {
    char parsing_buffer[255] = {0};
    char message_buffer[255] = {0};
    int parsing_buffer_i = 0;

    (*current_i)++;
    (*current_char)++;

    //Parsing  !ELEMENT or ! ATTRIBUTE
    while (!isspace(**current_char)) {
        parsing_buffer[parsing_buffer_i] = *(*current_char);
        parsing_buffer_i++;
        (*current_i)++;
        (*current_char)++;
    }
    parsing_buffer[parsing_buffer_i] = '\0';

    if (!strcmp(parsing_buffer, "!ELEMENT")) {
        return element_node_parse(document, size, current_i, current_char);
    } else {
        printf("GROSSE ERREUR MAMENE");
        return 0;
    }
}

int element_node_parse(dtd_document **document, size_t size, size_t *current_i, char **current_char) {
    char parsing_buffer[255] = {0};
    char message_buffer[255] = {0};
    int parsing_buffer_i = 0;

    element_node *current_element_node = init_dtd_node();
    current_element_node->rule_type = strdup(parsing_buffer);

    foward_spaces(current_char, current_i);

    //Parsing node name
    while (!isspace(**current_char)) {
        parsing_buffer[parsing_buffer_i] = **current_char;
        parsing_buffer_i++;
        (*current_i)++;
        (*current_char)++;
    }
    parsing_buffer[parsing_buffer_i] = '\0';
    current_element_node->tag_name = strdup(parsing_buffer);

    foward_spaces(current_char, current_i);

    //Parsing node rule
    if (**current_char != '(') {
        sprintf(message_buffer, "Error at %s node for %s node, can't parse rule(s)",
                current_element_node->rule_type, current_element_node->tag_name);
        logIt(message_buffer, 1);
        return 0;
    }

    (*current_char)++;
    (*current_i)++;

    while (**current_char != ')') {

        dtd_rule *current_rule = init_dtd_rule();
        foward_spaces(current_char, current_i);

        parsing_buffer_i = 0;
        while (!is_special(**current_char)) {
            parsing_buffer[parsing_buffer_i] = **current_char;
            parsing_buffer_i++;
            (*current_char)++;
            (*current_i)++;
        }
        parsing_buffer[parsing_buffer_i] = '\0';
        current_rule->rule_name = strdup(parsing_buffer);

        foward_spaces(current_char, current_i);

        if (is_node_spec(**current_char)) {
            current_rule->rule_spec = **current_char;
            (*current_char)++;
            (*current_i)++;
            foward_spaces(current_char, current_i);
        }

        if (!is_delim(*(*current_char))) {
            sprintf(message_buffer, "Error at %s node for %s node, %s have something wrong",
                    current_element_node->rule_type, current_element_node->tag_name, current_rule->rule_name);
            logIt(message_buffer, 1);
            return 0;
        }
        current_rule->rule_sep = **current_char;

        add_dtd_rule_at_end(&current_element_node->rule, current_rule);

        if (**current_char != ')') {
            (*current_char)++;
            (*current_i)++;
        }
    }


    /////////////////////////////////////////////////////////
    add_dtd_element_node_at_end(&(*document)->first_element_node, current_element_node);

    (*current_i)++;
    (*current_char)++;

    foward_spaces(current_char, current_i);

    if (**current_char != '>') {
        sprintf(message_buffer, "Error at %s node for %s node, rule do not close '>'",
                current_element_node->rule_type, current_element_node->tag_name);
        logIt(message_buffer, 1);
        return 0;
    }

    (*current_i)++;
    (*current_char)++;
    return 1;
}

void foward_spaces(char **current_char, size_t *current_i) {
    while (isspace(**current_char)) {
        (*current_char)++;
        (*current_i)++;
    }
}

int is_special(char c) {
    return isspace(c) || c == '+' || c == '*' || c == '?'
           || c == ',' || c == '|' || c == ')';
}

int is_delim(char c) {
    return c == ',' || c == '|' || c == ')';
}

int is_node_spec(char c) {
    return c == '+' || c == '*' || c == '?';
}