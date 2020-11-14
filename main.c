#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions/log.h"
#include "functions/xml_parser.h"
#include "functions/xml_finder.h"
#include "functions/dtd_rules.h"
#include "functions/dtd_parser.h"

char *logFile = "log.txt";

void initLogFile();

int main(int argc, char **argv) {
    initLogFile();

    char *buffer = dtd_to_string("dtd_example_1.dtd");
    linked_list *list = get_dtd_rules(buffer);
    parse_line_elements(list);

/*
    xml_document document;
    xml_document_load(&document, "xml_example_1.xml");

    xml_node_list *fields = get_nodes("field", document);
    pc_data(document.root_node->children.data[0]);

    xml_document_free(&document);
*/

    return 0;
}

void initLogFile() {
    if (setLogFileName(logFile)) {
        //Erreur, impossible d'avoir un fichier de log correct
        fprintf(stderr, "Error! log file not set\nPress any key to close program\n");
        getchar();
        exit(1);
    }
}