//
// Created by audre on 06/11/2020.
//

#ifndef CXML_DTD_RULES_H
#define CXML_DTD_RULES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"
#include "xml_parser.h"
#include "xml_finder.h"

int pc_data(xml_node *xmlNode);

int process_pc_data(const char *tag, xml_document document);

xml_attribute *get_node_attribute(const char *attribute_name, xml_node *xmlNode);

int node_contain_required_attribute(const char *required, xml_node *xmlNode);

int node_contain_optional_attribute(const char *required, xml_node *xmlNode);

int attribute_contain_required_value(xml_attribute *attribute, const char **str_list, int size);

//e*
int node_contain_only_children_optional(xml_node *node, const char *name);

//e
int node_contain_only_one_child_required(xml_node *node, const char *name);

//e?
int node_contain_only_one_child_optional(xml_node *node, const char *name);

//e+
int node_contain_only_children_required(xml_node *node, const char *name);

int check_node_child_position(xml_node *node, const char *name, int position);

#endif //CXML_DTD_RULES_H
