//
// Created by Unknow on 24/10/2020.
//

#include "dtd_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


linked_list *init_linked_list(char *data) {

    linked_list *linked_list_1 = malloc(sizeof(linked_list));

    linked_list_1->next = NULL;
    linked_list_1->previous = NULL;

    //TODO parser data en 3 éléments

    linked_list_1->data = strdup(data);

    return linked_list_1;
}

void add_data_at_end(linked_list *list, char *data) {

    while (list->next != NULL) {
        list = list->next;
    }

    linked_list *new = init_linked_list(data);

    list->next = new;
    new->previous = list;
}

linked_list *get_data(linked_list *list, int i) {
    if (i < 0) {
        return NULL;
    }

    while (i > 0 && list != NULL) {
        list = list->next;
        i--;
    }

    return list;
}

char *dtd_to_string(char *path) {
    size_t size;
    FILE *fichier = NULL;
    fichier = fopen(path, "r");
    if (fichier == NULL) {
        logIt("DTD file not found !");
        exit(1);
    }

    fseek(fichier, 0, SEEK_END);
    size = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);

    char *buf = malloc(sizeof(char) * (size + 1));
    fread(buf, sizeof(char), size, fichier);
    buf[size] = '\0';
    fclose(fichier);

    return buf;
}

linked_list *get_dtd_rules(char *buf) {
    linked_list *list = init_linked_list("");
    int i = 1;
    int elem_linked_list = 0, start_index = 0, end_index = 0;
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
    //free(buf);
    //free(lines);
}













