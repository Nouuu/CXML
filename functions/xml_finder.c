//
// Created by Unknow on 06/11/2020.
//

#include "xml_finder.h"


xml_node_list *get_nodes(const char *name, xml_document document) {
    if (document.root_node == NULL || name == NULL || !strlen(name)) {
        logIt("ERROR - You are trying to find nodes with empty name or with empty document");
        return NULL;
    }
    xml_node_list *list = malloc(sizeof(xml_node_list));
    xml_node_list_init(list);

    get_nodes_rec(list, document.root_node, name);

    return list;
}

void get_nodes_rec(xml_node_list *list, xml_node *node, const char *name) {
    if (!strcmp(name, node->tag)) {
        xml_node_list_add(list, node);
    }
    for (int i = 0; i < node->children.size; ++i) {
        get_nodes_rec(list, node->children.data[i], name);
    }
}