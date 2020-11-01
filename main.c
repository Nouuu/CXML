#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions/log.h"
#include "functions/xml.h"
#include "functions/xml_parser.h"

char *logFile = "log.txt";

void initLogFile();

FILE *openXMLFile(int argc, char **argv);

FILE *openDTDFile(int argc, char **argv);

int main(int argc, char **argv) {
    printf("Coucou");
    initLogFile();
/*
    FILE *xml_file = openXMLFile(argc, argv);
    readXML(xml_file);

    FILE *dtd_file = openDTDFile(argc, argv);
    readDTD(dtd_file, xml_file);

    fclose(xml_file);
    fclose(dtd_file);
*/

    xml_document document;
    if (xml_document_load(&document, "xml_files/test.xml")) {
        printf("%s\n", document.source);

        xml_node_list *fields = xml_node_children_by_tagname(xml_node_child(document.root_node, 0), "field");

        xml_document_free(&document);
    }

    return 0;
}

FILE *openXMLFile(int argc, char **argv) {
    FILE *fp = NULL;
    char message[255];
    if (argc == 3) {
        sprintf(message, "Open XML File : %s...", argv[1]);
        logIt(message);

        fp = fopen(argv[1], "r");

        if (fp == NULL) {
            logIt("File not found !");
            exit(1);
        } else {
            logIt("File opened");
        }
    } else {
        logIt("Wrong arg number, you must provide XML and DTD file path in argument");
        exit(1);
    }
    return fp;
}

FILE *openDTDFile(int argc, char **argv) {
    FILE *fp = NULL;
    char message[255];
    if (argc == 3) {
        sprintf(message, "Open DTD File : %s...", argv[2]);
        logIt(message);

        fp = fopen(argv[2], "r");

        if (fp == NULL) {
            logIt("File not found !");
            exit(1);
        } else {
            logIt("File opened");
        }
    } else {
        logIt("Wrong arg number, you must provide XML and DTD file path in argument");
        exit(1);
    }
    return fp;
}

void initLogFile() {
    if (setLogFileName(logFile)) {
        //Erreur, impossible d'avoir un fichier de log correct
        fprintf(stderr, "Error! log file not set\nPress any key to close program\n");
        getchar();
        exit(1);
    }
}