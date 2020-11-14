//
// Created by Unknow on 24/10/2020.
//

#include "dtd_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


dtd_node *init_linked_list() {

    dtd_node *linked_list_1 = malloc(sizeof(dtd_node));

    linked_list_1->next = NULL;
    //TODO parser data en 3 éléments

    //linked_list_1->tag_name = strdup(tag_name);

    return linked_list_1;
}

void add_data_at_end(dtd_node *list) {

    while (list->next != NULL) {
        list = list->next;
    }

    dtd_node *new = init_linked_list();

    list->next = new;
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
    int parsing_buffer_i = 0;
    size_t size = strlen(document->source);

    char *source = document->source;
    size_t current_i = 0;

    //////////// FIND !DOCTYPE //////////////
    while (source[current_i] != '<') {
        current_i++;
    }
    current_i++;

    while (!isspace(source[current_i])) {
        parsing_buffer[parsing_buffer_i] = source[current_i];
        parsing_buffer_i++;
        current_i++;
    }
    parsing_buffer[parsing_buffer_i] = '\0';

    if (strcmp(parsing_buffer, "!DOCTYPE") != 0) {

        logIt("First dtd node must be !DOCTYPE !", 1);
        return 0;
    }

    //////////// FIND DOCTYPE NODE //////////////

    while (isspace(source[current_i])) {
        current_i++;
    }

    parsing_buffer_i = 0;
    while (!isspace(source[current_i]) && source[current_i] != '[') {
        parsing_buffer[parsing_buffer_i] = source[current_i];
        parsing_buffer_i++;
        current_i++;
    }
    parsing_buffer[parsing_buffer_i] = '\0';

    document->root_node = strdup(parsing_buffer);

    //////////// GO TO '[' //////////////
    //TODO Vérifier le Root name !
/*
    while (source[current_i] != '[') {
        if (!isspace(source[current_i])) {
            logIt("", 1);
            return 0;
        }
        current_i++;
    }
*/
    parsing_buffer_i = 0;
    while (source[current_i] != '[') {
        current_i++;
    }
    current_i++;

    while (source[current_i] != ']') {
        //TODO TEST si '<'
        while(source[current_i] != '<'){
            current_i++;
        }
        current_i++;

        while (source[current_i] != '>'){
            //TODO décomposer en 3

                //TODO tag_name
                parsing_buffer[parsing_buffer_i] = source[current_i];
                parsing_buffer_i++;
                current_i++;

                //TODO name
                //TODO rule
        }
        //TODO TEST si '>
    current_i++;
    parsing_buffer[parsing_buffer_i] = '\0';
    }


    return 1;

/*
    dtd_node *list = init_linked_list("<!ELEMENT classrooms (classroom+)>");
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
        add_data_at_end(list, lines);

        elem_linked_list++;
        i++;
    }
    return list;
*/
    //free(buf);
    //free(lines);
}












