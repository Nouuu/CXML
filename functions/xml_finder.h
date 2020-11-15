//
// Created by Unknow on 06/11/2020.
//

#ifndef CXML_XML_FINDER_H
#define CXML_XML_FINDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "log.h"
#include "xml_parser.h"

xml_node_list * get_nodes(const char *name, xml_document document);

void get_nodes_rec(xml_node_list *list, xml_node *node, const char *name);

#endif //CXML_XML_FINDER_H
