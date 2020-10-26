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

bool xml_string_equals(xml_string *a, xml_string *b) {
    if (a->length != b->length) {
        return false;
    }

    size_t i;
    for (i = 0; i < a->length; ++i) {
        if (a->buffer[i] != b->buffer[i]) {
            return false;
        }
    }

    return true;
}

uint8_t *xml_string_clone(struct xml_string *s) {
    if (!s) {
        return 0;
    }

    uint8_t *clone = malloc(sizeof(uint8_t) * (s->length + 1));

    xml_string_copy(s, clone, s->length);
    clone[s->length] = 0;

    return clone;
}

void xml_string_free(xml_string *string) {
    free(string);
}

void xml_attribute_free(xml_attribute *attribute) {
    if (attribute->name) {
        xml_string_free(attribute->name);
    }
    if (attribute->content) {
        xml_string_free(attribute->content);
    }
    free(attribute);
}

void xml_node_free(xml_node *node) {
    if (node->name) {
        xml_string_free(node->name);
    }

    if (node->content) {
        xml_string_free(node->content);
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
