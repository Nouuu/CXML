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
    //linked_list_1->tag_name = strdup(tag_name);

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
    //logIt(buf);
    return buf;
}

linked_list *get_dtd_rules(char *buf) {
    linked_list *list = init_linked_list("<!ELEMENT classrooms (classroom+)>");
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
    //free(buf);
    //free(lines);
}

void parse_line_elements(linked_list *linkedList) {

    int i = 0, start_tag_name_index = 1, end_tag_name_index = 0;
    int start_name_index = 0, end_name_index = 0;
    int start_rule_index = 0, end_rule_index = 0;
    size_t sizeData = strlen(linkedList->data);

    while (linkedList->next != NULL){
        while (linkedList->data[i] != ' ' && i < sizeData) {
            i++;
        }
        // TAG NAME
        end_tag_name_index = i;
        char *tag_names = malloc(sizeof(char) * (255 + 1));
        strncpy(tag_names, linkedList->data + start_tag_name_index, (end_tag_name_index - start_tag_name_index) + 1);
        tag_names[(end_tag_name_index - start_tag_name_index) + 1] = '\0';
        linkedList->tag_name = tag_names;
        //logIt(tag_names);
        i++;

        // NAME
        start_name_index = i;
        char *names = malloc(sizeof(char) * (255 + 1));
        while (linkedList->data[i] != ' ' && i < sizeData) {
            i++;
        }
        end_name_index = i;
        strncpy(names, linkedList->data + start_name_index, (end_name_index - start_name_index) + 1);//TODO +1 ou pas ?
        names[(end_name_index - start_name_index) + 1] = '\0';
        linkedList->name = names;
        //logIt(names);
        i++;

        // RULE
        start_rule_index = i;
        char *rules = malloc(sizeof(char) * (255 + 1));
        while (linkedList->data[i] != ')' && i < sizeData){
            i++;
        }
        end_rule_index = i + 1;
        strncpy(rules, linkedList->data + start_rule_index,(end_rule_index - start_rule_index) + 1);
        rules[(end_rule_index - start_rule_index) + 1] = '\0';
        linkedList->rule = rules;
        //logIt(rules);


        // NEXT
        linkedList = linkedList->next;
        i = 0;
    }

}












