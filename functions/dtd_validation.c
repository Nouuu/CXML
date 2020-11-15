//
// Created by Unknow on 15/11/2020.
//

#include "dtd_validation.h"

int validate_dtd(const char *xml_path, const char *dtd_path) {
    char message[500] = {0};

    xml_document *xmlDocument = calloc(1, sizeof(xml_document));
    if (!xml_document_load(xmlDocument, xml_path)) {
        return FALSE;
    }

    dtd_document *dtdDocument = calloc(1, sizeof(dtd_document));
    if (!dtd_document_load(dtdDocument, dtd_path)) {
        return FALSE;
    }

    //Root node assertion
    if (strcmp(dtdDocument->root_node, xmlDocument->root_node->tag) != 0) {
        sprintf(message, "DTD Rule error - root node don't match. Expected '%s', got '%s'",
                dtdDocument->root_node, xmlDocument->root_node->tag);
        return FALSE;
    }

    return TRUE;
}