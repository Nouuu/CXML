//
// Created by Unknow on 15/11/2020.
//

#include "dtd_validation.h"

int validate_dtd(const char *xml_path, const char *dtd_path) {
//    char message[500] = {0};

    xml_document *xmlDocument = calloc(1, sizeof(xml_document));
    if (!xml_document_load(xmlDocument, xml_path)) {
        return FALSE;
    }

    dtd_document *dtdDocument = calloc(1, sizeof(dtd_document));
    if (!dtd_document_load(dtdDocument, dtd_path)) {
        return FALSE;
    }

    //Root node assertion
    if (!validate_doctype(dtdDocument, xmlDocument)) {
        return FALSE;
    }

    //Elements validation
    if (!validate_dtd_elements(dtdDocument, xmlDocument)) {
        return FALSE;
    }

    return validate_dtd_attributes(dtdDocument, xmlDocument);
}

int validate_doctype(dtd_document *dtdDocument, xml_document *xmlDocument) {
//    char message[500] = {0};

    if (dtdDocument->root_node) {
        if (strcmp(dtdDocument->root_node, xmlDocument->root_node->tag) != 0) {
            sprintf(message, "DTD Rule error - root node don't match. Expected '%s', got '%s'",
                    dtdDocument->root_node, xmlDocument->root_node->tag);
            logIt(message, 1);
            return FALSE;
        }
    }
    return TRUE;
}

int validate_dtd_elements(dtd_document *dtdDocument, xml_document *xmlDocument) {
//    char message[500] = {0};

    element_node *current_dtd_node = dtdDocument->first_element_node;
    while (current_dtd_node != NULL) {
        if (!validate_dtd_element(current_dtd_node, xmlDocument)) {
            return FALSE;
        }

        current_dtd_node = current_dtd_node->next;
    }
    return TRUE;
}

int validate_dtd_element(element_node *current_dtd_node, xml_document *xmlDocument) {
//    char message[500] = {0};
//On récupère dans le document xml toute les balises ayant le nom de la règle que l'on traite
    xml_node_list *current_xml_node_list = get_nodes(current_dtd_node->tag_name, xmlDocument);

    //On itère sur chacun des nodes récupérés pour valider la règle DTD
    for (int i = 0; i < current_xml_node_list->size; ++i) {
        //On récupère notre node
        xml_node *current_xml_node = current_xml_node_list->data[i];

        if (!validate_current_xml_node_dtd_element_rules(current_dtd_node, current_xml_node)) {

            return FALSE;
        }
    }
    free(current_xml_node_list);
    return TRUE;
}

int validate_dtd_attributes(dtd_document *dtdDocument, xml_document *xmlDocument) {

    attribute_node *current_dtd_node = dtdDocument->first_attribute_node;
    while (current_dtd_node != NULL) {
        if (!validate_dtd_attlist(current_dtd_node, xmlDocument)) {
            return FALSE;
        }

        current_dtd_node = current_dtd_node->next;
    }
    return TRUE;
}

int validate_dtd_attlist(attribute_node *current_dtd_node, xml_document *xmlDocument) {
    xml_node_list *current_xml_node_list = get_nodes(current_dtd_node->element_name, xmlDocument);

    if (!strcmp(current_dtd_node->attribute_type, "ID")) {
        //TODO construire une méthode qui va récupérer tout les att, vérifier le #REQUIRED si un manquant
        // recherche doublon sur la liste att
        printf("TODO ID !\n");
        return TRUE;
    } else {
        for (int i = 0; i < current_xml_node_list->size; ++i) {
            xml_node *current_xml_node = current_xml_node_list->data[i];

            if (!validate_current_xml_node_dtd_attribute_rule(current_dtd_node, current_xml_node)) {
                return FALSE;
            }
        }
    }

    free(current_xml_node_list);
    return TRUE;
}

int validate_current_xml_node_dtd_element_rules(element_node *current_dtd_node, xml_node *current_xml_node) {
//    char message[500] = {0};

    //On récupère la première règle DTD
    dtd_rule *current_rule = current_dtd_node->rule;

    //On itère tant qu'on trouve un élément
    char previous_rule_sep = 0;
    char previous_rule_result = 0;
    int j = 0;
    while (current_rule != NULL) {
        if (!validate_current_xml_node_dtd_element_current_rule(current_dtd_node, current_rule, current_xml_node,
                                                                &previous_rule_sep, &previous_rule_result, &j)) {
            return FALSE;
        }

        current_rule = current_rule->next;
    }

    if (j < current_xml_node->children.size) {
        sprintf(message,
                "DTD Rule error - '%s' element, '%s' child at position %d not supposed to be here",
                current_dtd_node->tag_name, current_xml_node->children.data[0]->tag, j + 1);
        logIt(message, 1);
        return FALSE;

    }
    return TRUE;
}

int validate_current_xml_node_dtd_element_current_rule(
        element_node *current_dtd_node,
        dtd_rule *current_rule, xml_node *current_xml_node,
        char *previous_rule_sep, char *previous_rule_result, int *j) {

//    char message[500] = {0};

    if (*previous_rule_sep == '|' && *previous_rule_result) {
        *previous_rule_sep = current_rule->rule_sep;
    } else {
        if (!strcmp(current_rule->rule_name, "#PCDATA")) {
            if (!validate_PCDATA_rule(current_dtd_node, current_rule, current_xml_node, previous_rule_sep,
                                      previous_rule_result)) {
                return FALSE;
            }
        } else {
            //On regarde quelle type de règle on a (+,*,?,rien)
            switch (current_rule->rule_spec) {
                case '+':
                    if (!validate_required_children_rule(current_dtd_node, current_rule, current_xml_node,
                                                         previous_rule_sep, previous_rule_result, j)) {
                        return FALSE;
                    }
                    break;
                case '*':
                    validate_optionnal_children_rule(current_rule, current_xml_node, previous_rule_sep,
                                                     previous_rule_result, j);
                    break;
                case '?':
                    validate_optionnal_child_rule(current_rule, current_xml_node, previous_rule_sep,
                                                  previous_rule_result, j);
                    break;
                default:
                    if (!validate_required_child_rule(current_dtd_node, current_rule, current_xml_node,
                                                      previous_rule_sep, previous_rule_result, j)) {
                        return FALSE;
                    }
                    break;
            }
        }
    }
    return TRUE;
}

int validate_current_xml_node_dtd_attribute_rule(attribute_node *current_dtd_node, xml_node *current_xml_node) {
    xml_attribute *attribute = get_node_attribute(current_dtd_node->attribute_name, current_xml_node);

    //Vérifie si l'attribue n'est pas présent et si il était obligatoire
    if (attribute == NULL) {
        if (!strcmp(current_dtd_node->attribute_option, "#REQUIRED")) {
            sprintf(message, "DTD Rule error - attribute '%s' is required on '%s' node",
                    current_dtd_node->attribute_name, current_dtd_node->element_name);
            logIt(message, 1);
            return FALSE;
        }
        return TRUE;
    }

    if (current_dtd_node->attribute_type[0] == '(') {
        // PIPE (h | f | m) TODO construire une méthode qui transforme ça en liste **str avec une size

        printf("TODO (a | b | c) !\n");
        return TRUE;
    } else if (!strcmp(current_dtd_node->attribute_type, "CDATA")) {
        printf("TODO CDATA !\n");
        return TRUE;

        //TODO juste vérifier que c'est po vide
    }

    return TRUE;
}

int validate_PCDATA_rule(element_node *current_dtd_node, dtd_rule *current_rule, xml_node *current_xml_node,
                         char *previous_rule_sep, char *previous_rule_result) {
    if (!pc_data(current_xml_node)) {
        if (current_rule->rule_sep == '|') {
            *previous_rule_sep = current_rule->rule_sep;
            *previous_rule_result = 0;
        } else {
            sprintf(message,
                    "DTD Rule error - '%s%c' rule for '%s' element is INVALID",
                    current_rule->rule_name, current_rule->rule_spec,
                    current_dtd_node->tag_name);
            logIt(message, 1);
            return FALSE;
        }
    }
    return TRUE;
}

int validate_required_child_rule(element_node *current_dtd_node, dtd_rule *current_rule, xml_node *current_xml_node,
                                 char *previous_rule_sep, char *previous_rule_result, int *j) {
    if (*j >= current_xml_node->children.size) {
        sprintf(message, "DTD Rule error - '%s%c' rule for '%s' element is out of range",
                current_rule->rule_name, current_rule->rule_spec,
                current_dtd_node->tag_name);
        logIt(message, 1);
        return FALSE;
    }

    if (!check_node_child_position(current_xml_node, current_rule->rule_name, *j)) {
        if (current_rule->rule_sep == '|') {
            *previous_rule_sep = current_rule->rule_sep;
            *previous_rule_result = 0;
            return TRUE;
        }
        sprintf(message,
                "DTD Rule error - '%s%c' rule for '%s' element is INVALID, got '%s'",
                current_rule->rule_name, current_rule->rule_spec,
                current_dtd_node->tag_name,
                current_xml_node->children.data[*j]->tag);
        logIt(message, 1);
        return FALSE;
    }
    (*j)++;
    *previous_rule_result = 1;
    *previous_rule_sep = current_rule->rule_sep;
    return TRUE;
}

int validate_optionnal_child_rule(dtd_rule *current_rule, xml_node *current_xml_node, char *previous_rule_sep,
                                  char *previous_rule_result, int *j) {
    if (*j < current_xml_node->children.size &&
        check_node_child_position(current_xml_node, current_rule->rule_name, *j)) {
        (*j)++;
    }
    *previous_rule_result = 1;
    *previous_rule_sep = current_rule->rule_sep;
    return TRUE;
}

int validate_required_children_rule(element_node *current_dtd_node, dtd_rule *current_rule, xml_node *current_xml_node,
                                    char *previous_rule_sep, char *previous_rule_result, int *j) {
    if (*j >= current_xml_node->children.size) {
        sprintf(message, "DTD Rule error - '%s%c' rule for '%s' element is out of range",
                current_rule->rule_name, current_rule->rule_spec,
                current_dtd_node->tag_name);
        logIt(message, 1);
        return FALSE;
    }

    if (!check_node_child_position(current_xml_node, current_rule->rule_name, *j)) {
        if (current_rule->rule_sep == '|') {
            *previous_rule_sep = current_rule->rule_sep;
            *previous_rule_result = 0;
            return TRUE;
        }
        sprintf(message,
                "DTD Rule error - '%s%c' rule for '%s' element is INVALID, got '%s'",
                current_rule->rule_name, current_rule->rule_spec,
                current_dtd_node->tag_name,
                current_xml_node->children.data[*j]->tag);
        logIt(message, 1);
        return FALSE;
    }
    while (*j < current_xml_node->children.size &&
           check_node_child_position(current_xml_node, current_rule->rule_name, *j)) {
        (*j)++;
    }
    *previous_rule_result = 1;
    *previous_rule_sep = current_rule->rule_sep;

    return TRUE;
}

int validate_optionnal_children_rule(dtd_rule *current_rule, xml_node *current_xml_node, char *previous_rule_sep,
                                     char *previous_rule_result, int *j) {
    while (*j < current_xml_node->children.size &&
           check_node_child_position(current_xml_node, current_rule->rule_name, *j)) {
        (*j)++;
    }
    *previous_rule_result = 1;
    *previous_rule_sep = current_rule->rule_sep;
    return TRUE;
}
