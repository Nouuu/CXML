//
// Created by Nospy on 26/10/2020.
//

#include "xml_parser.h"

size_t get_zero_terminated_array_attributes(xml_attribute **attributes) {
    size_t elements = 0;
    while (attributes[elements] != 0) {
        elements++;
    }
    return elements;
}

size_t get_zero_terminated_array_nodes(xml_node **nodes) {
    size_t elements = 0;
    while (nodes[elements] != 0) {
        elements++;
    }
    return elements;
}

char *xml_string_clone(char *s) {
    if (s == NULL || strlen(s) <= 0) {
        return 0;
    }

    char *clone = malloc(sizeof(uint8_t) * (strlen(s) + 1));

    strcpy(clone, s);

    return clone;
}

void xml_attribute_free(xml_attribute *attribute) {
    if (attribute->name) {
        free(attribute->name);
    }
    if (attribute->content) {
        free(attribute->content);
    }
    free(attribute);
}

void xml_node_free(xml_node *node) {
    if (node->name) {
        free(node->name);
    }

    if (node->content) {
        free(node->content);
    }

    xml_attribute **at_cursor = node->attributes;
    while (*at_cursor != 0) {
        xml_attribute_free(*at_cursor);
        at_cursor++;
    }
    free(node->attributes);

    xml_node **it_cursor = node->children;
    while (*it_cursor) {
        xml_node_free(*it_cursor);
        it_cursor++;
    }
    free(node->children);

    free(node);
}

//TODO line 314
