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