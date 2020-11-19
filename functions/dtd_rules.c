//
// Created by audre on 06/11/2020.
//

#include "dtd_rules.h"

int pc_data(xml_node *xmlNode) {
    char message[200] = {0};
    if (xmlNode->children.size > 0) {
//        sprintf(message, "%s node supposed to be pcdata but have children", xmlNode->tag);
//        logIt(message, 0);
        return 0;
    }

    if (xmlNode->inner_text != NULL && strlen(xmlNode->inner_text) > 0) {
        return 1;
    }

//    sprintf(message, "%s node is not pcdata", xmlNode->tag);
//    logIt(message, 0);
    return 0;

}

int process_pc_data(const char *tag, xml_document *document) {
    xml_node_list *list = get_nodes(tag, document);

    for (int i = 0; i < list->size; i++) {
        if (!pc_data(list->data[i])) {
            return 0;
        }
    }
    return 1;
}

xml_attribute *get_node_attribute(const char *attribute_name, xml_node *xmlNode) {
    char message[200] = {0};
    for (int i = 0; i < xmlNode->attribute_list.size; i++) {
        if (!strcmp(xmlNode->attribute_list.data[i].key, attribute_name)) {
            return &xmlNode->attribute_list.data[i];
        }
    }
//    sprintf(message, "%s node not have |%s| key", xmlNode->tag, attribute_name);
//    logIt(message, 1);
    return NULL;
}

int node_contain_required_attribute(const char *required, xml_node *xmlNode) {
    char message[200] = {0};
    if (node_contain_optional_attribute(required, xmlNode)) {
        return 1;
    }
    sprintf(message, "%s node no contain |%s| but is required", xmlNode->tag, required);
    logIt(message, 1);
    return 0;
}

int node_contain_optional_attribute(const char *required, xml_node *xmlNode) {
    if (get_node_attribute(required, xmlNode)) {
        return 1;
    }
    return 0;
}

int attribute_contain_required_value(xml_attribute *attribute, const char **str_list, int size) {
    char message[200] = {0};
    for (int i = 0; i < size; i++) {
        if (!strcmp(attribute->value, str_list[i])) {
            return 1;
        }
    }
    sprintf(message, "%s attribute not supposed to have |%s| value", attribute->key, attribute->value);
    logIt(message, 1);
    return 0;
}

// e*
int node_contain_only_children_optional(xml_node *node, const char *name, int position) {
    char message[200] = {0};
    for (int i = 0; i < node->children.size; i++) {
        if (!strcmp(node->children.data[i]->tag, name)) {
            return 1;
        }
    }
    sprintf(message, "%s node have no |%s| children (optional)", node->tag, name);
    logIt(message, 1);
    return 0;
}

// e
int node_contain_only_one_child_required(xml_node *node, const char *name, int position) {
    char message[200] = {0};
    if (node->children.size == 1) {
        for (int i = 0; i < node->children.size; i++) {
            if (!strcmp(node->children.data[i]->tag, name)) {
                return 1;
            }
        }
    }
    sprintf(message, "%s node have no only one child called |%s|", node->tag, name);
    logIt(message, 1);
    return 0;
}

// e?
int node_contain_only_one_child_optional(xml_node *node, const char *name, int position) {
    char message[200] = {0};
    if (node->children.size == 0 || node->children.size == 1) {
        for (int i = 0; i < node->children.size; i++) {
            if (!strcmp(node->children.data[i]->tag, name)) {
                return 1;
            }
        }
    }
    sprintf(message, "%s node have no only one or none child called |%s|", node->tag, name);
    logIt(message, 1);
    return 0;
}

// e+
int node_contain_only_children_required(xml_node *node, const char *name) {
    char message[200] = {0};
    if (node->children.size >= 1) {
        for (int i = 0; i < node->children.size; i++) {
            if (!strcmp(node->children.data[i]->tag, name)) {
                return 1;
            }
        }
    }
    sprintf(message, "%s node have no one or many |%s| children", node->tag, name);
    logIt(message, 1);
    return 0;
}

int check_node_child_position(xml_node *node, const char *name, int position) {
    char message[200] = {0};
    if (node->children.size <= position) {
        sprintf(message, "Trying to access children at position %d, but node %s has only %d children",
                position, node->tag, node->children.size);
        logIt(message, 1);
        return 0;
    }
    if (!strcmp(node->children.data[position]->tag, name)) {
        return 1;
    }
//    sprintf(message, "%s node have no |%s| children at the %d position", node->tag, name, position);
//    logIt(message,1);
    return 0;
}