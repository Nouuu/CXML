//
// Created by Nospy on 27/10/2020.
//

#include "xml_parser_2.h"

int xml_document_load(xml_document *document, const char *path) {
    char message_buffer[300] = {0};
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

    char parsing_buffer[256] = {0};
    int parsing_buffer_i = 0;
    int i = 0;

    xml_node *current_node = NULL;

    while (document->source[i] != '\0') {

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

            // getting tag name
            i++;
            while (document->source[i] != '>') {
                parsing_buffer[parsing_buffer_i] = document->source[i];
                parsing_buffer_i++;
                i++;
            }
            parsing_buffer[parsing_buffer_i] = '\0';
            current_node->tag = strdup(parsing_buffer);

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
    return node;
}

void xml_node_free(xml_node *node) {
    if (node != NULL) {
        if (node->tag) {
            free(node->tag);
        }
        if (node->inner_text) {
            free(node->inner_text);
        }
        free(node);
    }
}


