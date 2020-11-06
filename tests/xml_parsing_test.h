//
// Created by Unknow on 06/11/2020.
//

#ifndef CXML_XML_PARSING_TEST_H
#define CXML_XML_PARSING_TEST_H

#if defined(_WIN32)

#include <windows.h>

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../functions/log.h"
#include "../functions/xml_parser.h"
#include "../functions/xml_finder.h"


void run_xml_parse_test();

void change_console_color();

void reset_console_color();

void run_test_1(const char *path);

//void run_test_2(const char *path);
//
//void run_test_3(const char *path);
//
//void run_test_4(const char *path);
//
//void run_test_5(const char *path);
//
//void run_test_6(const char *path);
//
//void run_test_7(const char *path);

void check_document_load(xml_document *document, const char *path);

void check_document_version(xml_document document, const char *version);

void check_encoding_version(xml_document document, const char *version);

void check_root_tag(xml_document document, const char *name);

void check_root_children_tag_name(xml_document document, int size, char **tags);

void check_root_children_inner_text(xml_document document, int size, char **inner_text);

#endif //CXML_XML_PARSING_TEST_H
