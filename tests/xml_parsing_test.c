//
// Created by Unknow on 06/11/2020.
//

#include "xml_parsing_test.h"

void run_xml_parse_test() {

    run_test_1("tests/test_1.xml");

}

void run_test_1(const char *path) {
    xml_document document;

    assert(xml_document_load(&document, path));
    assert(!strcmp(document.version, "1.0"));
    assert(document.encoding == NULL);

    xml_document_free(&document);

}

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