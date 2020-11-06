#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions/log.h"
#include "functions/xml_parser.h"
#include "functions/xml_finder.h"
#include "functions/dtd_rules.h"

char *logFile = "log.txt";

void initLogFile();

int main(int argc, char **argv) {
    initLogFile();

    xml_document document;
    xml_document_load(&document, "xml_files/xml_example_1.xml");

        xml_node_list *fields = get_nodes("field", document);
    pcData(document.root_node->children.data[0]);


        xml_document_free(&document);

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