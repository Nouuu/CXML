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
/**
 * Echos xml parser error
 * @param parser
 * @param offset
 * @param message
 */
void xml_parser_error(xml_parser *parser, xml_parser_offset offset, char const *message) {
    int row = 0;
    int column = 0;

    size_t character = MAX(0, MIN(strlen(parser->buffer), parser->position + offset));

    size_t position;
    for (position = 0; position < character; position++) {
        column++;

        if (parser->buffer[position] == '\n') {
            row++;
            column = 0;
        }
    }

    if (offset != NO_CHARACTER) {
        fprintf(stderr, "xml_parser_error at %d:%d (is %c): %s\n",
                row + 1, column, parser->buffer[character], message
        );
    } else {
        fprintf(stderr, "xml_parser_error at %d:%d: %s\n",
                row + 1, column, message
        );
    }
}

uint8_t xml_parser_peek(xml_parser *parser, size_t n) {
    size_t position = parser->position;

    while (position < strlen(parser->buffer)) {
        if (!isspace(parser->buffer[position])) {
            if (n == 0) {
                return parser->buffer[position];
            } else {
                n--;
            }
        }
        position++;
    }

    return 0;
}

void xml_parser_inc(xml_parser *parser, size_t n) {
    parser->position += n;

    if (parser->position >= strlen(parser->buffer)) {
        parser->position = strlen(parser->buffer) - 1;
    }
}

void xml_skip_whitespace(xml_parser *parser) {
    while (isspace(parser->buffer[parser->position])) {
        if (parser->position + 1 >= strlen(parser->buffer)) {
            return;
        } else {
            parser->position++;
        }
    }
}
