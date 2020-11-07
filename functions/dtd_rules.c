//
// Created by audre on 06/11/2020.
//

#include "dtd_rules.h"

int pc_data(xml_node *xmlNode) {
    char message[200] = {0};
    if (xmlNode->children.size > 0) {
        sprintf(message, "%s node supposed to be pcdata but have children", xmlNode->tag);
        logIt(message);
        return 0;
    }

    if (xmlNode->inner_text != NULL && strlen(xmlNode->inner_text) > 0) {
        return 1;
    }

    sprintf(message, "%s node is not pcdata", xmlNode->tag);
    logIt(message);
    return 0;

}

int process_pc_data(const char *tag, xml_document document) {
    xml_node_list* list = get_nodes(tag, document);

    for(int i = 0; i < list->size; i++) {
        if(!pc_data(list->data[i])) {
            return 0;
        }
    }
    return 1;
}

xml_attribute *get_node_attribute(const char *attribute_name, xml_node *xmlNode) {
    char message[200] = {0};
    for(int i = 0; i < xmlNode->attribute_list.size; i++) {
        if(!strcmp(xmlNode->attribute_list.data[i].key, attribute_name)) {
            return &xmlNode->attribute_list.data[i];
        }
    }
    sprintf(message, "%s node not have |%s| key", xmlNode->tag, attribute_name);
    logIt(message);
    return NULL;
}

int node_contain_required_attribute(const char *required, xml_node *xmlNode) {
    if(get_node_attribute(required, xmlNode)) {
        return 1;
    } else {
        return 0;
    }
}