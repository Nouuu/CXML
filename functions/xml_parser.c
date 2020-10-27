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

xml_attribute **xml_find_attributes(xml_parser *parser, char *tag_open) {
    char *tmp;
    char *rest = NULL;
    char *token;
    char *str_name;
    char *str_content;
    const char *start_name;
    const char *start_content;
    size_t old_elements;
    size_t new_elements;
    xml_attribute *new_attribute;
    xml_attribute **attributes;
    size_t position;

    attributes = malloc(sizeof(xml_attribute *));
    attributes[0] = 0;

    tmp = xml_string_clone(tag_open);

    token = strtok_r(tmp, " ", &rest); // skip the first value
    if (token != NULL) {

        for (token = strtok_r(NULL, " ", &rest); token != NULL; token = strtok_r(NULL, " ", &rest)) {
            str_name = malloc(strlen(token) + 1);
            str_content = malloc(strlen(token) + 1);
            if (sscanf(token, "%[^=]=\"%[^\"]", str_name, str_content) != 2) {
                if (sscanf(token, "%[^=]=\'%[^\']", str_name, str_content) != 2) {
                    free(str_name);
                    free(str_content);
                    continue;
                }
            }
            position = token - tmp;
            start_name = &tag_open[position];
            start_content = &tag_open[position + strlen(str_name) + 2];

            new_attribute = malloc(sizeof(struct xml_attribute));
            new_attribute->name = (char *) start_name;
            new_attribute->content = (char *) start_content;

            old_elements = get_zero_terminated_array_attributes(attributes);
            new_elements = old_elements + 1;
            attributes = realloc(attributes, (new_elements + 1) * sizeof(struct xml_attributes *));

            attributes[new_elements - 1] = new_attribute;
            attributes[new_elements] = 0;


            free(str_name);
            free(str_content);
        }
    }

    free(tmp);
    return attributes;
}