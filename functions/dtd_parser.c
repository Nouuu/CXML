//
// Created by Unknow on 24/10/2020.
//

#include "dtd_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


dtd_node *init_dtd_node() {

    dtd_node *linked_list_1 = malloc(sizeof(dtd_node));

    linked_list_1->next = NULL;
    linked_list_1->rule_type = NULL;
    linked_list_1->tag_name = NULL;
    linked_list_1->first_rule = NULL;

    return linked_list_1;
}

void add_dtd_node_at_end(dtd_node **list, dtd_node *new_node) {

    if (*list == NULL) {

        *list = new_node;

    } else {

        dtd_node *current_node = *list;
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

dtd_node *get_data(dtd_node *list, int i) {
    if (i < 0) {
        return NULL;
    }

    while (i > 0 && list != NULL) {
        list = list->next;
        i--;
    }

    return list;
}

char *get_dtd_document_source(char *path) {

    size_t size;
    FILE *fichier = NULL;
    fichier = fopen(path, "r");
    if (fichier == NULL) {
        logIt("DTD file not found !", 0);
        exit(1);
    }

    fseek(fichier, 0, SEEK_END);
    size = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);

    char *buf = malloc(sizeof(char) * (size + 1));
    fread(buf, sizeof(char), size, fichier);
    buf[size] = '\0';
    fclose(fichier);
    //logIt(buf);
    return buf;
}

int parse_dtd(dtd_document *document, dtd_node *list) {

    char parsing_buffer[255] = {0};
    char message_buffer[255] = {0};
    int parsing_buffer_i = 0;
    size_t size = strlen(document->source);

    char *current_char = document->source;
    size_t current_i = 0;

    //////////// FIND !DOCTYPE //////////////
    while (*current_char != '<') {
        current_i++;
        current_char++;
    }
    current_i++;
    current_char++;

    while (!isspace(*current_char)) {
        parsing_buffer[parsing_buffer_i] = *current_char;
        parsing_buffer_i++;
        current_i++;
        current_char++;
    }
    parsing_buffer[parsing_buffer_i] = '\0';

    if (strcmp(parsing_buffer, "!DOCTYPE") != 0) {

        logIt("First dtd node must be !DOCTYPE !", 1);
        return 0;
    }

    //////////// FIND DOCTYPE NODE //////////////

    foward_spaces(&current_char, &current_i);

    parsing_buffer_i = 0;
    while (!isspace(*current_char) && *current_char != '[') {
        parsing_buffer[parsing_buffer_i] = *current_char;
        parsing_buffer_i++;
        current_i++;
        current_char++;
    }
    parsing_buffer[parsing_buffer_i] = '\0';

    document->root_node = strdup(parsing_buffer);

    //////////// GO TO '[' //////////////

    while (*current_char != '[') {
        if (!isspace(*current_char)) {
            logIt("DOCTYPE Node contain other things than juste root node name", 1);
            return 0;
        }
        current_i++;
        current_char++;
    }

    current_i++;
    current_char++;

    while (*current_char != ']') {

        //Start node
        if (*current_char == '<') {
            dtd_node *current_node = init_dtd_node();
            current_i++;
            current_char++;

            //Parsing  !ELEMENT
            parsing_buffer_i = 0;
            while (!isspace(*current_char)) {
                parsing_buffer[parsing_buffer_i] = *current_char;
                parsing_buffer_i++;
                current_i++;
                current_char++;
            }
            parsing_buffer[parsing_buffer_i] = '\0';
            current_node->rule_type = strdup(parsing_buffer);

            foward_spaces(&current_char, &current_i);

            //Parsing node name
            parsing_buffer_i = 0;
            while (!isspace(*current_char)) {
                parsing_buffer[parsing_buffer_i] = *current_char;
                parsing_buffer_i++;
                current_i++;
                current_char++;
            }
            parsing_buffer[parsing_buffer_i] = '\0';
            current_node->tag_name = strdup(parsing_buffer);

            foward_spaces(&current_char, &current_i);

            //Parsing node rule
            if (*current_char != '(') {
                sprintf(message_buffer, "Error at %s node for %s node, can't parse rule(s)",
                        current_node->rule_type, current_node->tag_name);
                logIt(message_buffer, 1);
                return 0;
            }

            current_char++;
            current_i++;

            while (*current_char != ')') {

                dtd_rule *current_rule = init_dtd_rule();
                foward_spaces(&current_char, &current_i);

                parsing_buffer_i = 0;
                while (!is_special(*current_char)) {
                    parsing_buffer[parsing_buffer_i] = *current_char;
                    parsing_buffer_i++;
                    current_char++;
                    current_i++;
                }
                parsing_buffer[parsing_buffer_i] = '\0';
                current_rule->rule_name = strdup(parsing_buffer);

                foward_spaces(&current_char, &current_i);

                if (is_node_spec(*current_char)) {
                    current_rule->rule_spec = *current_char;
                    current_char++;
                    current_i++;
                    foward_spaces(&current_char, &current_i);
                }

                if (!is_delim(*current_char)) {
                    sprintf(message_buffer, "Error at %s node for %s node, %s have something wrong",
                            current_node->rule_type, current_node->tag_name, current_rule->rule_name);
                    return 0;
                }
                current_rule->rule_sep = *current_char;

                add_dtd_rule_at_end(&current_node->first_rule, current_rule);

                if (*current_char != ')') {
                    current_char++;
                    current_i++;
                }
            }


            /////////////////////////////////////////////////////////
            add_dtd_node_at_end(&document->first_node, current_node);

            current_i++;
            current_char++;
        }
        current_char++;
        current_i++;
        if (current_i >= size) {
            logIt("Can't find endind array carracter", 1);
            return 0;
        }
    }


    return 1;

/*
    dtd_node *list = init_dtd_node("<!ELEMENT classrooms (classroom+)>");
    int i = 1;
    int elem_linked_list = 0,start_index = 0,end_index = 0;
    size_t size = 255;
    char *lines = malloc(sizeof(char) * (size + 1));
    while (i < strlen(buf)) {
        while (buf[i] != '<' && i < strlen(buf)) {
            i++;
        }
        start_index = i;
        while (buf[i] != '>' && i < strlen(buf)) {
            i++;
        }
        end_index = i;

        strncpy(lines, buf + start_index, (end_index - start_index) + 1);
        lines[(end_index - start_index) + 1] = '\0';

        //printf("%s\n", lines);
        add_dtd_node_at_end(list, lines);

        elem_linked_list++;
        i++;
    }
    return list;
*/
    //free(buf);
    //free(lines);
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