#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions/log.h"
#include "functions/xml_parser.h"
#include "functions/xml_finder.h"
#include "functions/dtd_rules.h"
#include "functions/dtd_parser.h"
#include "tests/xml_parsing_test.h"

char *logFile = "log.txt";

void initLogFile();

int main(int argc, char **argv) {
    initLogFile();

    /////////////////////
//    run_xml_parse_test();
    /////////////////////


    char *buffer = dtd_to_string("dtd_files/dtd_example_1.dtd");

    linked_list *list = NULL;
    parse_dtd(buffer, list);
//    parse_line_elements(list);

/*
    xml_document document;
    xml_document_load(&document, "xml_example_1.xml");

    xml_node_list *fields = get_nodes("field", document);

    process_pc_data("classroom", document);
    get_node_attribute("key", document.root_node);
    node_contain_required_attribute("key", document.root_node);

    char **children_tag = malloc(sizeof(char *) * 4);
    children_tag[0] = strdup("classroom");
    children_tag[1] = strdup("key");
    children_tag[2] = strdup("test");
    children_tag[3] = strdup("text");
    attribute_contain_required_value(document.root_node->attribute_list.data, (const char **) children_tag,
                                     4);

    node_contain_only_children_optional(document.root_node, "classroom");
    node_contain_only_one_child_required(document.root_node, "classroom");
    node_contain_only_one_child_optional(document.root_node, "classroom");
    node_contain_only_children_required(document.root_node, "classroom");

    check_node_child_position(document.root_node, "classroom", 2);

    xml_document_free(&document);

    return 0;*/
}

void initLogFile() {
    if (setLogFileName(logFile)) {
        //Erreur, impossible d'avoir un fichier de log correct
        fprintf(stderr, "Error! log file not set\nPress any key to close program\n");
        getchar();
        exit(1);
    }
}