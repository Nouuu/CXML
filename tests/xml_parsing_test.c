//
// Created by Unknow on 06/11/2020.
//

#include "xml_parsing_test.h"

void change_console_color() {
#ifdef __unix__
    printf("\033[1;32m");
#elif defined(_WIN32)
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, 2);
#endif

}

void reset_console_color() {
#ifdef __unix__
    printf("\033[0m");
#elif defined(_WIN32)
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, 0);
#endif

}

void run_xml_parse_test() {
    change_console_color();

    printf("\n---- Running xml parsing test ----\n");

    run_test_1("tests/test_1.xml");


    printf("\n---- All tests passed ! ----------\n");

    reset_console_color();
}

void run_test_1(const char *path) {
    printf("Running test 1\n");
    xml_document document;
    check_document_load(&document, "tests/test_1.xml");

    check_document_version(document, "1.0");

    check_encoding_version(document, NULL);

    check_root_tag(document, "classrooms");

    char **children_tag = malloc(sizeof(char *) * 4);
    children_tag[0] = "classroom";
    children_tag[1] = "classroom";
    children_tag[2] = "classroom";
    children_tag[3] = "classroom";
    check_root_children_tag_name(document, 4, children_tag);
    free(children_tag);

    char **children_inner_text = malloc(sizeof(char *) * 4);
    children_inner_text[0] = "AL";
    children_inner_text[1] = "IABD";
    children_inner_text[2] = "MOC";
    children_inner_text[3] = "IBC";
    check_root_children_inner_text(document, 4, children_inner_text);
    free(children_inner_text);

    xml_document_free(&document);
    printf("Test 1 passed\n\n");
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

void check_document_load(xml_document *document, const char *path) {
    printf("\tParsing document %s\n", path);
    assert(xml_document_load(document, path));
}

void check_document_version(xml_document document, const char *version) {
    printf("\tChecking document version\n");
    if (version == NULL) {
        assert(document.version == NULL);
    } else {
        assert(!strcmp(document.version, version));
    }
}

void check_encoding_version(xml_document document, const char *version) {
    printf("\tChecking encoding version\n");
    if (version == NULL) {
        assert(document.encoding == NULL);
    } else {
        assert(!strcmp(document.encoding, version));
    }
}

void check_root_tag(xml_document document, const char *name) {
    printf("\tChecking root tag\n");
    assert(!strcmp(document.root_node->tag, name));
}

void check_root_children_tag_name(xml_document document, int size, char **tags) {
    printf("\tChecking root children tag name\n");
    assert(document.root_node->children.size == size);
    for (int i = 0; i < size; ++i) {
        assert(!strcmp(document.root_node->children.data[i]->tag, tags[i]));
    }
}

void check_root_children_inner_text(xml_document document, int size, char **tags) {
    printf("\tChecking root children inner text\n");
    assert(document.root_node->children.size == size);
    for (int i = 0; i < size; ++i) {
        assert(!strcmp(document.root_node->children.data[i]->inner_text, tags[i]));
    }
}