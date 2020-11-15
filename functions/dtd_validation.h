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


int validate_dtd(const char *xml_path, const char *dtd_path);


#endif //CXML_DTD_VALIDATION_H
