//
// Created by Unknow on 24/10/2020.
//

#ifndef CXML_XML_H
#define CXML_XML_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"

void readXML(FILE *fp);
char *getBetween(char *xml_str, char *tag, size_t *end_pos);

#endif //CXML_XML_H
