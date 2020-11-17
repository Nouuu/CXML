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
        logIt(message, 1);
        return FALSE;
    }

    //On récupère la première balise DTD
    element_node *current_dtd_node = dtdDocument->first_element_node;
    while (current_dtd_node != NULL) {
        //On part du principe pour le moment que current node est bien !ELEMENT

        //On récupère dans le document xml toute les balises ayant le nom de la règle que l'on traite
        xml_node_list *current_xml_node_list = get_nodes(current_dtd_node->tag_name, xmlDocument);

        //On itère sur chacun des nodes récupérés pour valider la règle DTD
        for (int i = 0; i < current_xml_node_list->size; ++i) {
            //On récupère notre node
            xml_node *current_xml_node = current_xml_node_list->data[i];

            //On récupère la première règle DTD
            dtd_rule *current_rule = current_dtd_node->rule;

            //On itère tant qu'on trouve un élément
            char previous_rule_sep = 0;
            char previous_rule_result = 0;
            int j = 0;
            while (current_rule != NULL) {
                if (previous_rule_sep == '|' && previous_rule_result) {
                    previous_rule_sep = current_rule->rule_sep;
                } else {
                    if (!strcmp(current_rule->rule_name, "#PCDATA")) {
                        if (!pc_data(current_xml_node)) {
                            if (current_rule->rule_sep == '|') {
                                previous_rule_sep = current_rule->rule_sep;
                                previous_rule_result = 0;
                            } else {
                                sprintf(message,
                                        "DTD Rule error - '%s%c' rule for '%s' element is INVALID",
                                        current_rule->rule_name, current_rule->rule_spec,
                                        current_dtd_node->tag_name);
                                logIt(message, 1);
                                return FALSE;
                            }
                        }
                    } else {
                        //On regarde quelle type de règle on a (+,*,?,rien)
                        switch (current_rule->rule_spec) {
                            case '+':
                                if (j >= current_xml_node->children.size) {
                                    sprintf(message, "DTD Rule error - '%s%c' rule for '%s' element is out of range",
                                            current_rule->rule_name, current_rule->rule_spec,
                                            current_dtd_node->tag_name);
                                    logIt(message, 1);
                                    return FALSE;
                                }

                                if (!check_node_child_position(current_xml_node, current_rule->rule_name, j)) {
                                    if (current_rule->rule_sep == '|') {
                                        previous_rule_sep = current_rule->rule_sep;
                                        previous_rule_result = 0;
                                        break;
                                    }
                                    sprintf(message,
                                            "DTD Rule error - '%s%c' rule for '%s' element is INVALID, got '%s'",
                                            current_rule->rule_name, current_rule->rule_spec,
                                            current_dtd_node->tag_name,
                                            current_xml_node->children.data[j]->tag);
                                    logIt(message, 1);
                                    return FALSE;
                                }
                                while (j < current_xml_node->children.size &&
                                       check_node_child_position(current_xml_node, current_rule->rule_name, j)) {
                                    j++;
                                }
                                previous_rule_result = 1;
                                previous_rule_sep = current_rule->rule_sep;
                                break;
                            case '*':
                                while (j < current_xml_node->children.size &&
                                       check_node_child_position(current_xml_node, current_rule->rule_name, j)) {
                                    j++;
                                }
                                previous_rule_result = 1;
                                previous_rule_sep = current_rule->rule_sep;
                                break;
                            case '?':
                                if (j < current_xml_node->children.size &&
                                    check_node_child_position(current_xml_node, current_rule->rule_name, j)) {
                                    j++;
                                }
                                previous_rule_result = 1;
                                previous_rule_sep = current_rule->rule_sep;
                                break;
                            default:
                                if (j >= current_xml_node->children.size) {
                                    sprintf(message, "DTD Rule error - '%s%c' rule for '%s' element is out of range",
                                            current_rule->rule_name, current_rule->rule_spec,
                                            current_dtd_node->tag_name);
                                    logIt(message, 1);
                                    return FALSE;
                                }

                                if (!check_node_child_position(current_xml_node, current_rule->rule_name, j)) {
                                    if (current_rule->rule_sep == '|') {
                                        previous_rule_sep = current_rule->rule_sep;
                                        previous_rule_result = 0;
                                        break;
                                    }
                                    sprintf(message,
                                            "DTD Rule error - '%s%c' rule for '%s' element is INVALID, got '%s'",
                                            current_rule->rule_name, current_rule->rule_spec,
                                            current_dtd_node->tag_name,
                                            current_xml_node->children.data[j]->tag);
                                    logIt(message, 1);
                                    return FALSE;
                                }
                                j++;
                                previous_rule_result = 1;
                                previous_rule_sep = current_rule->rule_sep;

                                break;
                        }
                    }
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
        }

        current_dtd_node = current_dtd_node->next;
    }

    return TRUE;
}