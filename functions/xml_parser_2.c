//
// Created by Nospy on 27/10/2020.
//

#include "xml_parser_2.h"

int xml_document_load(xml_document *document, const char *path) {
    char message_buffer[500] = {0};
    FILE *fp = NULL;
    size_t size;

    fp = fopen(path, "r");
    if (!fp) {
        sprintf(message_buffer, "Could not load file from '%s'", path);
        logIt(message_buffer);
        return FALSE;
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    document->source = malloc(sizeof(char) * (size + 1));
    fread(document->source, sizeof(char), size, fp);
    fclose(fp);

    document->source[size] = '\0';
    document->root_node = xml_node_new(NULL);

    char parsing_buffer[500] = {0};
    int parsing_buffer_i = 0;
    int i = 0;

    xml_node *current_node = NULL;
    while (document->source[i] != '\0' && i < size) {

        if (document->source[i] == '<') {
            parsing_buffer[parsing_buffer_i] = '\0';

            // parsing_ buffer is here inner text
            if (parsing_buffer_i > 0) {
                if (!current_node) {
                    sprintf(message_buffer, "ERROR - Text outside of document : '%s'", parsing_buffer);
                    logIt(message_buffer);
                    return FALSE;
                }

                current_node->inner_text = strdup(parsing_buffer);
                parsing_buffer_i = 0;
            }

            // ending node
            if (document->source[i + 1] == '/') {
                i += 2;
                while (document->source[i] != '>') {
                    parsing_buffer[parsing_buffer_i] = document->source[i];
                    parsing_buffer_i++;
                    i++;
                }
                parsing_buffer[parsing_buffer_i] = '\0';

                if (!current_node) {
                    logIt("ERROR - You are already at the root of document");
                    return FALSE;
                }
                if (strcmp(current_node->tag, parsing_buffer) != 0) {
                    sprintf(message_buffer,
                            "ERROR - Closing tag don't match with opening tag. Expected :'%s', got :'%s'",
                            current_node->tag, parsing_buffer);
                    logIt(message_buffer);
                    return FALSE;
                }

                current_node = current_node->parent;
                i++;
                continue;
            }

            // setting current node
            if (!current_node) {
                current_node = document->root_node;
            } else {
                current_node = xml_node_new(current_node);
            }


            // getting tag name beginning
            i++;
            xml_attribute current_attribute;
            current_attribute.key = NULL;
            current_attribute.value = NULL;

            while (document->source[i] != '>' && i < size) {
                parsing_buffer[parsing_buffer_i] = document->source[i];
                parsing_buffer_i++;
                i++;

                //Tag name ending
                if (isspace(document->source[i]) && !current_node->tag) {
                    printf("Tag end : |%s|\n", parsing_buffer);
                    parsing_buffer[parsing_buffer_i] = '\0';
                    current_node->tag = strdup(parsing_buffer);
                    parsing_buffer_i = 0;
                    i++;
                    continue;
                }

                //Pas sur ?
                if (isspace(parsing_buffer[parsing_buffer_i - 1])) {
                    parsing_buffer_i--;
                    continue;
                }

                //Getting attribute key
                if (document->source[i] == '=') {
                    parsing_buffer[parsing_buffer_i] = '\0';
                    current_attribute.key = strdup(parsing_buffer);
                    parsing_buffer_i = 0;
                    continue;
                }

                //getting attribute value
                if (document->source[i] == '"' || document->source[i] == '\'') {
                    if (!current_attribute.key) {
                        logIt("ERROR - attribute's value has no key");
                        return FALSE;
                    }

                    char choosen_quote = document->source[i];
                    parsing_buffer_i = 0;
                    i++;

                    while (document->source[i] != choosen_quote) {
                        if (i == size - 1) {
                            sprintf(message_buffer,
                                    "ERROR - You forgot to close quote on your attribute '%s' in your tag '%s'",
                                    current_attribute.key, current_node->tag);
                            logIt(message_buffer);
                            return FALSE;
                        }

                        parsing_buffer[parsing_buffer_i] = document->source[i];
                        parsing_buffer_i++;
                        i++;
                    }

                    parsing_buffer[parsing_buffer_i] = '\0';
                    current_attribute.value = strdup(parsing_buffer);
                    xml_attribute_list_add(&current_node->attribute_list, &current_attribute);

                    current_attribute.value = NULL;
                    current_attribute.key = NULL;

                    parsing_buffer_i = 0;
                    i++;
                    continue;
                }
            }

            // Set tag name if none
            parsing_buffer[parsing_buffer_i] = '\0';
            if (!current_node->tag) {
                current_node->tag = strdup(parsing_buffer);
            }

            // resetting parsing buffer
            parsing_buffer_i = 0;
            i++;
            continue;
        } else {
            parsing_buffer[parsing_buffer_i] = document->source[i];
            parsing_buffer_i++;
            i++;
        }
    }

    return TRUE;
}

void xml_document_free(xml_document *document) {
    free(document->source);
    xml_node_free(document->root_node);
}

xml_node *xml_node_new(xml_node *parent) {
    xml_node *node = malloc(sizeof(xml_node));
    node->tag = NULL;
    node->inner_text = NULL;
    node->parent = parent;
    xml_attribute_list_init(&node->attribute_list);
    return node;
}

void xml_node_free(xml_node *node) {
    if (node) {
        if (node->tag) {
            free(node->tag);
        }
        if (node->inner_text) {
            free(node->inner_text);
        }
        free(node);

        int i;
        for (i = 0; i < node->attribute_list.size; ++i) {
            xml_attribute_free(&node->attribute_list.data[i]);
        }
    }
}

void xml_attribute_free(xml_attribute *attribute) {
    if (attribute) {
        if (attribute->key) {
            free(attribute->key);
        }
        if (attribute->value) {
            free(attribute->value);
        }
    }
}

void xml_attribute_list_init(xml_attribute_list *attribute_list) {
    attribute_list->capacity = 1;
    attribute_list->size = 0;
    attribute_list->data = malloc(sizeof(xml_attribute) * attribute_list->capacity);
}

void xml_attribute_list_add(xml_attribute_list *attribute_list, xml_attribute *attribute) {
    while (attribute_list->size >= attribute_list->capacity) {
        attribute_list->capacity *= 2;
        attribute_list->data = realloc(attribute_list->data, sizeof(xml_attribute) * attribute_list->capacity);
    }

    attribute_list->data[attribute_list->size] = *attribute;
    attribute_list->size++;
}




