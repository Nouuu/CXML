#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions/log.h"
#include "functions/xml_parser.h"
#include "functions/xml_finder.h"
#include "functions/dtd_rules.h"
#include "functions/dtd_parser.h"
#include "functions/dtd_validation.h"
#include "tests/xml_parsing_test.h"

char *logFile = "log.txt";

void initLogFile();

int main(int argc, char **argv) {
    initLogFile();

    /////////////////////
    run_xml_parse_test();
    /////////////////////

}

void initLogFile() {
    if (setLogFileName(logFile)) {
        //Erreur, impossible d'avoir un fichier de log correct
        fprintf(stderr, "Error! log file not set\nPress any key to close program\n");
        getchar();
        exit(1);
    }
}