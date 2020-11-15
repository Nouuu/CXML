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

    run_test_1("xml_files/test_1.xml");

    run_test_2("xml_files/test_2.xml");

    run_test_3("xml_files/test_3.xml");

    run_test_4("xml_files/test_4.xml");

    run_test_5("xml_files/test_5.xml");

    run_test_6("xml_files/test_6.xml");

    printf("\n---- All tests passed ! ----------\n");

    reset_console_color();
}

void run_test_1(const char *path) {
    printf("---- Running test 1\n");
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
    free_string_array(children_tag, 4);


    char **children_inner_text = malloc(sizeof(char *) * 4);
    children_inner_text[0] = strdup("AL");
    children_inner_text[1] = strdup("IABD");
    children_inner_text[2] = strdup("MOC");
    children_inner_text[3] = strdup("IBC");
    check_node_children_inner_text(document.root_node, 4, children_inner_text);
    free_string_array(children_inner_text, 4);

    xml_document_free(&document);
    printf("---- Test 1 passed\n\n");
}

void run_test_2(const char *path) {
    printf("---- Running test 2\n");
    xml_document document;
    check_document_load(&document, path);

    check_document_version(document, NULL);

    check_encoding_version(document, NULL);

    check_node_tag(document.root_node, "ESGI");

    check_node_inner_text(document.root_node, "IBC YOUPI");

    char **children_tag = malloc(sizeof(char *));
    children_tag[0] = strdup("classroom");
    check_node_children_tag_name(document.root_node, 1, children_tag);
    free_string_array(children_tag, 1);

    char **children_inner_text = malloc(sizeof(char *));
    children_inner_text[0] = strdup("AL");
    check_node_children_inner_text(document.root_node, 1, children_inner_text);
    free_string_array(children_inner_text, 1);

    char **attribute_keys = malloc(sizeof(char *));
    attribute_keys[0] = strdup("key");
    char **attribute_values = malloc(sizeof(char *));
    attribute_values[0] = strdup("value");
    check_node_attributes(document.root_node, 1, (const char **) attribute_keys, (const char **) attribute_values);
    free_string_array(attribute_keys, 1);
    free_string_array(attribute_values, 1);

    attribute_keys = malloc(sizeof(char *));
    attribute_values = malloc(sizeof(char *));
    attribute_keys[0] = strdup("other_key");
    attribute_values[0] = strdup("other_value");
    check_node_attributes(document.root_node->children.data[0], 1, (const char **) attribute_keys,
                          (const char **) attribute_values);
    free_string_array(attribute_keys, 1);
    free_string_array(attribute_values, 1);

    xml_document_free(&document);
    printf("---- Test 2 passed\n\n");
}

void run_test_3(const char *path) {
    printf("---- Running test 3\n");
    xml_document document;
    check_document_load(&document, path);

    check_document_version(document, "1.0");

    check_encoding_version(document, "UTF-8");

    check_node_tag(document.root_node, "struct");

    check_node_inner_text(document.root_node, "cc cc2");

    char **attribute_keys = malloc(sizeof(char *) * 2);
    attribute_keys[0] = strdup("key");
    attribute_keys[1] = strdup("another");
    char **attribute_values = malloc(sizeof(char *) * 2);
    attribute_values[0] = strdup("value");
    attribute_values[1] = strdup("other value");
    check_node_attributes(document.root_node, 2, (const char **) attribute_keys, (const char **) attribute_values);
    free_string_array(attribute_keys, 2);
    free_string_array(attribute_values, 2);

    char **children_tag = malloc(sizeof(char *) * 4);
    children_tag[0] = strdup("field");
    children_tag[1] = strdup("pasfield");
    children_tag[2] = strdup("field");
    children_tag[3] = strdup("inline");
    check_node_children_tag_name(document.root_node, 4, children_tag);
    free_string_array(children_tag, 4);

    char **children_inner_text = malloc(sizeof(char *) * 4);
    children_inner_text[0] = strdup("coucou");
    children_inner_text[1] = NULL;
    children_inner_text[2] = NULL;
    children_inner_text[3] = NULL;
    check_node_children_inner_text(document.root_node, 4, children_inner_text);
    free_string_array(children_inner_text, 4);

    attribute_keys = malloc(sizeof(char *) * 2);
    attribute_keys[0] = strdup("name");
    attribute_keys[1] = strdup("type");
    attribute_values = malloc(sizeof(char *) * 2);
    attribute_values[0] = strdup("name");
    attribute_values[1] = strdup("string");
    check_node_attributes(document.root_node->children.data[0], 2, (const char **) attribute_keys,
                          (const char **) attribute_values);
    free_string_array(attribute_keys, 2);
    free_string_array(attribute_values, 2);

    attribute_keys = malloc(sizeof(char *) * 2);
    attribute_keys[0] = strdup("name");
    attribute_keys[1] = strdup("type");
    attribute_values = malloc(sizeof(char *) * 2);
    attribute_values[0] = strdup("second");
    attribute_values[1] = strdup("int");
    check_node_attributes(document.root_node->children.data[2], 2, (const char **) attribute_keys,
                          (const char **) attribute_values);
    free_string_array(attribute_keys, 2);
    free_string_array(attribute_values, 2);

    check_node_children_tag_name(document.root_node->children.data[0], 0, NULL);
    check_node_children_tag_name(document.root_node->children.data[2], 0, NULL);
    check_node_children_tag_name(document.root_node->children.data[3], 0, NULL);

    children_tag = malloc(sizeof(char *));
    children_tag[0] = strdup("field");
    check_node_children_tag_name(document.root_node->children.data[1], 1, children_tag);
    check_node_children_tag_name(document.root_node->children.data[1]->children.data[0], 1, children_tag);
    free_string_array(children_tag, 1);

    children_inner_text = malloc(sizeof(char *));
    children_inner_text[0] = NULL;
    check_node_children_inner_text(document.root_node->children.data[1], 1, children_inner_text);
    check_node_children_inner_text(document.root_node->children.data[1]->children.data[0], 1, children_inner_text);
    free_string_array(children_inner_text, 1);

    check_node_children_tag_name(document.root_node->children.data[1]->children.data[0]->children.data[0], 0, NULL);

    xml_document_free(&document);
    printf("---- Test 3 passed\n\n");
}

void run_test_4(const char *path) {
    printf("---- Running test 4 (incomplete)\n");
    xml_document document;
    check_document_load(&document, path);

    check_document_version(document, "1.0");

    check_encoding_version(document, NULL);

    check_node_tag(document.root_node, "ecole");

    char **children_tag = malloc(sizeof(char *));
    children_tag[0] = strdup("classes");
    check_node_children_tag_name(document.root_node, 1, children_tag);
    free_string_array(children_tag, 1);


    char **children_inner_text = malloc(sizeof(char *));
    children_inner_text[0] = NULL;
    check_node_children_inner_text(document.root_node, 1, children_inner_text);
    free_string_array(children_inner_text, 1);

    xml_document_free(&document);
    printf("---- Test 4 passed\n\n");
}

void run_test_5(const char *path) {
    printf("---- Running test 5\n");
    xml_document document;
    check_document_load_syntax_error(&document, path);

    xml_document_free(&document);
    printf("---- Test 5 passed\n\n");
}

void run_test_6(const char *path) {
    printf("---- Running test 6\n");
    xml_document document;
    check_document_load_syntax_error(&document, path);

    xml_document_free(&document);
    printf("---- Test 6 passed\n\n");
}

//void run_test_7(const char *path);

void check_document_load(xml_document *document, const char *path) {
    printf("\tParsing document %s\n", path);
    assert(xml_document_load(document, path));
}

void check_document_load_syntax_error(xml_document *document, const char *path) {
    printf("\tParsing document %s, expecting syntax error\n", path);
    assert(!xml_document_load(document, path));

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
    assert(inner_text == NULL ? node->inner_text == NULL : !strcmp(node->inner_text, inner_text));
}

void free_string_array(char **str_list, int size) {
    for (int i = 0; i < size; ++i) {
        if (str_list[i] != NULL) {
            free(str_list[i]);
        }
    }
    free(str_list);
}
