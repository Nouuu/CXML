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

    run_test_2("tests/test_2.xml");

    run_test_3("tests/test_3.xml");

    printf("\n---- All tests passed ! ----------\n");

    reset_console_color();
}

void run_test_1(const char *path) {
    printf("Running test 1\n");
    xml_document document;
    check_document_load(&document, path);

    check_document_version(document, "1.0");

    check_encoding_version(document, NULL);

    check_node_tag(document.root_node, "classrooms");

    char **children_tag = malloc(sizeof(char *) * 4);
    children_tag[0] = strdup("classroom");
    children_tag[1] = strdup("classroom");
    children_tag[2] = strdup("classroom");
    children_tag[3] = strdup("classroom");
    check_node_children_tag_name(document.root_node, 4, children_tag);
    free(children_tag[0]);
    free(children_tag[1]);
    free(children_tag[2]);
    free(children_tag[3]);
    free(children_tag);

    char **children_inner_text = malloc(sizeof(char *) * 4);
    children_inner_text[0] = strdup("AL");
    children_inner_text[1] = strdup("IABD");
    children_inner_text[2] = strdup("MOC");
    children_inner_text[3] = strdup("IBC");
    check_node_children_inner_text(document.root_node, 4, children_inner_text);
    free(children_inner_text[0]);
    free(children_inner_text[1]);
    free(children_inner_text[2]);
    free(children_inner_text[3]);
    free(children_inner_text);

    xml_document_free(&document);
    printf("Test 1 passed\n\n");
}

void run_test_2(const char *path) {
    printf("Running test 2\n");
    xml_document document;
    check_document_load(&document, path);

    check_document_version(document, NULL);

    check_encoding_version(document, NULL);

    check_node_tag(document.root_node, "ESGI");

    check_node_inner_text(document.root_node, "IBC YOUPI");

    char **children_tag = malloc(sizeof(char *));
    children_tag[0] = strdup("classroom");
    check_node_children_tag_name(document.root_node, 1, children_tag);
    free(children_tag[0]);
    free(children_tag);

    char **children_inner_text = malloc(sizeof(char *));
    children_inner_text[0] = strdup("AL");
    check_node_children_inner_text(document.root_node, 1, children_inner_text);
    free(children_inner_text[0]);
    free(children_inner_text);

    char **attribute_keys = malloc(sizeof(char *));
    attribute_keys[0] = strdup("key");
    char **attribute_values = malloc(sizeof(char *));
    attribute_values[0] = strdup("value");
    check_node_attributes(document.root_node, 1, (const char **) attribute_keys, (const char **) attribute_values);

    free(attribute_keys[0]);
    free(attribute_values[0]);
    attribute_keys[0] = strdup("other_key");
    attribute_values[0] = strdup("other_value");
    check_node_attributes(document.root_node->children.data[0], 1, (const char **) attribute_keys,
                          (const char **) attribute_values);
    free(attribute_keys[0]);
    free(attribute_values[0]);
    free(attribute_keys);
    free(attribute_values);

    xml_document_free(&document);
    printf("Test 2 passed\n\n");
}

void run_test_3(const char *path) {
    printf("Running test 3\n");
    xml_document document;
    check_document_load(&document, path);

    check_document_version(document, "1.0");

    check_encoding_version(document, "UTF-8");

    check_node_tag(document.root_node, "struct");

    check_node_inner_text(document.root_node, "cc cc2");

    xml_document_free(&document);
    printf("Test 3 passed\n\n");
}
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

void check_node_tag(xml_node *node, const char *name) {
    printf("\tChecking %s tag\n", node->tag);
    assert(!strcmp(node->tag, name));
}

void check_node_attributes(xml_node *node, int size, const char **keys, const char **values) {
    printf("\tChecking %s attributes\n", node->tag);
    assert(node->attribute_list.size == size);
    for (int i = 0; i < size; i++) {
        assert(!strcmp(node->attribute_list.data[i].key, keys[i]));
        assert(!strcmp(node->attribute_list.data[i].value, values[i]));
    }
}

void check_node_children_tag_name(xml_node *node, int size, char **tags) {
    printf("\tChecking %s children tag name\n", node->tag);
    assert(node->children.size == size);
    for (int i = 0; i < size; ++i) {
        assert(!strcmp(node->children.data[i]->tag, tags[i]));
    }
}

void check_node_children_inner_text(xml_node *node, int size, char **inner_text) {
    printf("\tChecking %s children inner text\n", node->tag);
    assert(node->children.size == size);
    for (int i = 0; i < size; ++i) {
        check_node_inner_text(node->children.data[i], inner_text[i]);
    }
}

void check_node_inner_text(xml_node *node, const char *inner_text) {
    printf("\tChecking %s inner text\n", node->tag);
    assert(!strcmp(node->inner_text, inner_text));

}
