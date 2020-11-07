//
// Created by Nospy on 27/10/2020.
//

#include "xml_parser.h"

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
    document->encoding = NULL;
    document->version = NULL;

    return parse_xml_file(document, size);
}

int parse_xml_file(xml_document *document, size_t size) {
    char message_buffer[500] = {0};
    char parsing_buffer[500] = {0};
    int parsing_buffer_i = 0;
    int i = 0;

    xml_node *current_node = NULL;

    while (document->source[i] != '\0' && i < size) {

        if (document->source[i] == '<') {
            int return_code = parse_xml_carret_open(document, &i, &parsing_buffer_i, &current_node, parsing_buffer,
                                                    message_buffer, size);
            if (return_code == FALSE) {
                return FALSE;
            } else if (return_code == 2) {
                continue;
            }
        } else {
            parsing_buffer[parsing_buffer_i] = document->source[i];
            parsing_buffer_i++;
            i++;
        }
    }
    return TRUE;
}

int parse_xml_carret_open(xml_document *document, int *i, int *parsing_buffer_i, xml_node **current_node,
                          char *parsing_buffer, char *message_buffer, size_t size) {

    parsing_buffer[(*parsing_buffer_i)] = '\0';

    // parsing_ buffer is here inner text
    if ((*parsing_buffer_i) > 0 && !string_only_contain_space_characters(parsing_buffer)) {

        if (!(*current_node)) {
            sprintf(message_buffer, "ERROR - Text outside of document : '%s'", parsing_buffer);
            logIt(message_buffer);
            return FALSE;
        }

        if (!(*current_node)->inner_text) {

            (*current_node)->inner_text = strtrim_space(parsing_buffer);
        } else {
            (*current_node)->inner_text = strcat_realloc((*current_node)->inner_text, parsing_buffer);
        }
        (*parsing_buffer_i) = 0;
    } else {
        (*parsing_buffer_i) = 0;
        parsing_buffer[(*parsing_buffer_i)] = '\0';
    }

    // ending node
    if (document->source[(*i) + 1] == '/') {
        (*i) += 2;
        while (document->source[(*i)] != '>') {
            parsing_buffer[(*parsing_buffer_i)] = document->source[(*i)];
            (*parsing_buffer_i)++;
            (*i)++;
        }
        parsing_buffer[(*parsing_buffer_i)] = '\0';

        if (!(*current_node)) {
            logIt("ERROR - You are already at the root of document");
            return FALSE;
        }
        if (strcmp((*current_node)->tag, parsing_buffer) != 0) {
            sprintf(message_buffer,
                    "ERROR - Closing tag don't match with opening tag. Expected :'%s', got :'%s'",
                    (*current_node)->tag, parsing_buffer);
            logIt(message_buffer);
            return FALSE;
        }

        (*current_node) = (*current_node)->parent;
        (*parsing_buffer_i) = 0;
        parsing_buffer[(*parsing_buffer_i)] = '\0';
        (*i)++;
        return 2;
    }


    //Look like there is a special node
    if (document->source[(*i) + 1] == '!') {
        while (!isspace(document->source[(*i)]) && document->source[(*i)] != '>') {
            parsing_buffer[(*parsing_buffer_i)] = document->source[(*i)];
            (*parsing_buffer_i)++;
            (*i)++;
        }
        parsing_buffer[(*parsing_buffer_i)] = '\0';

        // checking comment
        if (!strcmp(parsing_buffer, "<!--")) {
            while (ends_with(parsing_buffer, "-->") == FALSE) {
                if ((*i) >= size - 1) {
                    logIt("ERROR - You have unclosed comment in your XML file");
                    return FALSE;
                }
                parsing_buffer[(*parsing_buffer_i)] = document->source[(*i)];
                (*parsing_buffer_i)++;
                (*i)++;
            }
            parsing_buffer[(*parsing_buffer_i)] = '\0';
            printf("Found comment : \n|%s|\n\n\n", parsing_buffer);

//                    (*i)++;
            return 2;
        }
    }

    //xml spec tag
    if (document->source[(*i) + 1] == '?') {
        while (!isspace(document->source[(*i)]) && document->source[(*i)] != '>') {
            parsing_buffer[(*parsing_buffer_i)] = document->source[(*i)];
            (*parsing_buffer_i)++;
            (*i)++;
        }
        parsing_buffer[(*parsing_buffer_i)] = '\0';

        // checking xml special tag
        if (!strcmp(parsing_buffer, "<?xml")) {
            (*parsing_buffer_i) = 0;

            xml_node *specifications = xml_node_new(NULL);
            parse_attributes(document->source, &(*i), parsing_buffer, &(*parsing_buffer_i), specifications, size);

            document->version = xml_node_attribute_value(specifications, "version") == NULL ?
                                NULL : strdup(xml_node_attribute_value(specifications, "version"));
            document->encoding = xml_node_attribute_value(specifications, "encoding") == NULL ?
                                 NULL : strdup(xml_node_attribute_value(specifications, "encoding"));

            xml_node_free(specifications);
            (*parsing_buffer_i) = 0;
            (*i)++;
            return 2;
        }
    }
    // setting current node
    if (!(*current_node)) {
        (*current_node) = document->root_node;
    } else {
        (*current_node) = xml_node_new((*current_node));
    }

    // getting tag name beginning
    (*i)++;
    if (parse_attributes(document->source, &(*i), parsing_buffer, &(*parsing_buffer_i), (*current_node), size) ==
        INLINE_TAG) {
        (*current_node) = (*current_node)->parent;
        (*i)++;
        (*parsing_buffer_i) = 0;
        parsing_buffer[(*parsing_buffer_i)] = '\0';
        return 2;
    }

    // Set tag name if none
    parsing_buffer[(*parsing_buffer_i)] = '\0';
    if (!(*current_node)->tag) {
        (*current_node)->tag = strdup(parsing_buffer);
    }

    // resetting parsing buffer
    (*parsing_buffer_i) = 0;
    parsing_buffer[(*parsing_buffer_i)] = '\0';
    (*i)++;
    return 2;
}

void xml_document_free(xml_document *document) {
    free(document->source);
    if (document->version) {
        free(document->version);
    }
    if (document->encoding) {
        free(document->encoding);
    }
    xml_node_free(document->root_node);
}

xml_node *xml_node_new(xml_node *parent) {
    xml_node *node = malloc(sizeof(xml_node));
    node->tag = NULL;
    node->inner_text = NULL;
    node->parent = parent;
    xml_attribute_list_init(&node->attribute_list);
    xml_node_list_init(&node->children);
    if (parent) {
        xml_node_list_add(&parent->children, node);
    }
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
        for (i = 0; i < node->attribute_list.size; i++) {
            xml_attribute_free(&node->attribute_list.data[i]);
        }
        for (i = 0; i < node->children.size; i++) {
            xml_node_free(node->children.data[i]);
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

void xml_node_list_init(xml_node_list *node_list) {
    node_list->capacity = 1;
    node_list->size = 0;
    node_list->data = malloc(sizeof(xml_node) * node_list->capacity);

}

void xml_node_list_add(xml_node_list *node_list, xml_node *node) {
    while (node_list->size >= node_list->capacity) {
        node_list->capacity *= 2;
        node_list->data = realloc(node_list->data, sizeof(xml_node *) * node_list->capacity);
    }

    node_list->data[node_list->size] = node;
    node_list->size++;

}

xml_node *xml_node_child(xml_node *parent, int index) {
    char message[255] = {0};
    if (index >= parent->children.size) {
        sprintf(message, "Trying to get node child out of range. parent node '%s' child index '%d'", parent->tag,
                index);
        logIt(message);
        return NULL;
    }
    return parent->children.data[index];
}


int ends_with(const char *str, const char *end_str) {
    size_t str_len = strlen(str);
    size_t end_str_len = strlen(end_str);

    if (str_len < end_str_len) {
        return FALSE;
    }

    return strcmp(str + str_len - end_str_len, end_str) == 0;
}

tag_type
parse_attributes(const char *source, int *i, char *parsing_buffer, int *parsing_buffer_i, xml_node *current_node,
                 size_t size) {
    char message_buffer[500] = {0};
    xml_attribute current_attribute;
    current_attribute.key = NULL;
    current_attribute.value = NULL;

    while (source[(*i)] != '>' && (*i) < size) {
        parsing_buffer[(*parsing_buffer_i)] = source[(*i)];
        (*parsing_buffer_i)++;
        (*i)++;

        //Tag name ending
        if (isspace(source[(*i)]) && !current_node->tag) {
            parsing_buffer[(*parsing_buffer_i)] = '\0';
            current_node->tag = strdup(parsing_buffer);
            (*parsing_buffer_i) = 0;
            (*i)++;
            continue;
        }

        //Pas sur ?
        if (isspace(parsing_buffer[(*parsing_buffer_i) - 1])) {
            (*parsing_buffer_i)--;
            continue;
        }

        //Getting attribute key
        if (source[(*i)] == '=') {
            parsing_buffer[(*parsing_buffer_i)] = '\0';
            current_attribute.key = strdup(parsing_buffer);
            (*parsing_buffer_i) = 0;
            continue;
        }

        //getting attribute value
        if (source[(*i)] == '"' || source[(*i)] == '\'') {
            if (!current_attribute.key) {
                logIt("ERROR - attribute's value has no key");
                exit(FALSE);
            }

            char choosen_quote = source[(*i)];
            (*parsing_buffer_i) = 0;
            (*i)++;

            while (source[(*i)] != choosen_quote) {
                if ((*i) == size - 1) {
                    sprintf(message_buffer,
                            "ERROR - You forgot to close quote on your attribute '%s' in your tag '%s'",
                            current_attribute.key, current_node->tag);
                    logIt(message_buffer);
                    exit(FALSE);
                }

                parsing_buffer[(*parsing_buffer_i)] = source[(*i)];
                (*parsing_buffer_i)++;
                (*i)++;
            }

            parsing_buffer[(*parsing_buffer_i)] = '\0';
            current_attribute.value = strdup(parsing_buffer);
            xml_attribute_list_add(&current_node->attribute_list, &current_attribute);

            current_attribute.value = NULL;
            current_attribute.key = NULL;

            (*parsing_buffer_i) = 0;
            (*i)++;
            continue;
        }
    }
    if (source[(*i) - 1] == '/') {
        parsing_buffer[(*parsing_buffer_i) - 1] = '\0';
        if (!current_node->tag) {
            current_node->tag = strdup(parsing_buffer);
        }
        (*i)++;
        return INLINE_TAG;
    }
    return START_TAG;
}

char *xml_node_attribute_value(xml_node *node, const char *key) {
    char message[255] = {0};
    xml_attribute attribute;
    for (int i = 0; i < node->attribute_list.size; i++) {
        attribute = node->attribute_list.data[i];
        if (!strcmp(attribute.key, key)) {
            return attribute.value;
        }
    }
    if (strcmp(key, "encoding") != 0 && strcmp(key, "version") != 0) {
        sprintf(message, "Cannot find attribute '%s' on node '%s'", key, node->tag);
        logIt(message);
    }
    return NULL;
}

xml_attribute *xml_node_attribute(xml_node *node, const char *key) {
    char message[255] = {0};
    xml_attribute *attribute;
    for (int i = 0; i < node->attribute_list.size; i++) {
        attribute = &node->attribute_list.data[i];
        if (!strcmp(attribute->key, key)) {
            return attribute;
        }
    }
    sprintf(message, "Cannot find attribute '%s' on node '%s'", key, node->tag);
    logIt(message);
    return NULL;
}

xml_node *xml_node_get(xml_node_list node_list, int index) {
    char message[255] = {0};
    if (index >= node_list.size) {
        sprintf(message, "Trying to get node out of range. index '%d'", index);
        logIt(message);
        return NULL;
    }
    return node_list.data[index];
}

void xml_node_list_free(xml_node_list *node_list) {
    int i;

    ////Pas sur sur
    for (i = 0; i < node_list->size; i++) {
        if (node_list->data[i] != NULL) {
            free(node_list->data[i]);
        }
    }
    free(node_list);
}

xml_node_list *xml_node_children_by_tagname(xml_node *parent, const char *tag) {
    int i;
    xml_node *child = NULL;
    xml_node_list *list = malloc(sizeof(xml_node_list));
    xml_node_list_init(list);

    for (i = 0; i < parent->children.size; i++) {
        child = parent->children.data[i];
        if (!strcmp(child->tag, tag)) {
            xml_node_list_add(list, child);
        }
    }
    return list;
}

int string_only_contain_space_characters(const char *string) {
    int i;
    for (i = 0; i < strlen(string); i++) {
        if (!isspace(string[i])) {
            return FALSE;
        }
    }
    return TRUE;
}

char *strcat_realloc(char *str_1, char *str_2) {
    char *temp = strtrim_space(str_2);
    str_1 = realloc(str_1, strlen(str_1) + strlen(str_2) + 2);
    strcat(str_1, " ");
    strcat(str_1, temp);
    free(temp);
    return str_1;
}



