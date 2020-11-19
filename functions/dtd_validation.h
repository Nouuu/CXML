//
// Created by Unknow on 15/11/2020.
//

#ifndef CXML_DTD_VALIDATION_H
#define CXML_DTD_VALIDATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "xml_parser.h"
#include "xml_finder.h"
#include "dtd_rules.h"
#include "dtd_parser.h"
#include "log.h"
#include "str_tools.h"

static char message[500] = {0};

int validate_dtd(const char *xml_path, const char *dtd_path);

int validate_doctype(dtd_document *dtdDocument, xml_document *xmlDocument);

int validate_dtd_elements(dtd_document *dtdDocument, xml_document *xmlDocument);

int validate_dtd_attributes(dtd_document *dtdDocument, xml_document *xmlDocument);

int validate_dtd_element(element_node *current_dtd_node, xml_document *xmlDocument);

int validate_dtd_attlist(attribute_node *current_dtd_node, xml_document *xmlDocument);

int validate_current_xml_node_dtd_element_rules(element_node *current_dtd_node, xml_node *current_xml_node);

int validate_current_xml_node_dtd_attribute_rule(attribute_node *current_dtd_node, xml_node *current_xml_node);

int validate_current_xml_node_dtd_element_current_rule(element_node *current_dtd_node,
                                                       dtd_rule *current_rule, xml_node *current_xml_node,
                                                       char *previous_rule_sep, char *previous_rule_result, int *j);

int validate_PCDATA_rule(element_node *current_dtd_node, dtd_rule *current_rule, xml_node *current_xml_node,
                         char *previous_rule_sep, char *previous_rule_result);

int validate_required_child_rule(element_node *current_dtd_node, dtd_rule *current_rule, xml_node *current_xml_node,
                                 char *previous_rule_sep, char *previous_rule_result, int *j);

int validate_optionnal_child_rule(dtd_rule *current_rule, xml_node *current_xml_node, char *previous_rule_sep,
                                  char *previous_rule_result, int *j);

int validate_required_children_rule(element_node *current_dtd_node, dtd_rule *current_rule, xml_node *current_xml_node,
                                    char *previous_rule_sep, char *previous_rule_result, int *j);

int validate_optionnal_children_rule(dtd_rule *current_rule, xml_node *current_xml_node, char *previous_rule_sep,
                                     char *previous_rule_result, int *j);

int validate_attribute_rule_pipe(xml_attribute *attribute, char *attribute_authorized_values);

#endif //CXML_DTD_VALIDATION_H
