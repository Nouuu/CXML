//
// Created by audre on 15/11/2020.
//

#include <stdio.h>
#include <string.h>

char **menu();
int verif_xml(char *xml_file);
int verif_dtd(char *dtd_file);

int main(int argc, char **argv) {
    if(argc == 3) {
        printf("%s", *argv);
    } else {
        argv = menu();
    }

    printf("%s", *argv);
    return 0;
}

char **menu() {
    char **files_name;
    char *dtd_file, *xml_file;
    int cpt = 0, choice = 0;

    printf("You don't put files in args so please, choose an option : \n");
    do {
        printf("1 - Select dtd file \n");
        printf("2 - Select xml file \n");

        scanf("%i", &choice);

        switch(choice) {
            case 1: {
                printf("What is the name of your dtd file ?");
                scanf("%s", dtd_file);
                cpt += verif_dtd(dtd_file);
                break;
            }
            case 2: {
                printf("What is the name of your xml file ?");
                scanf("%s", xml_file);
                cpt += verif_xml(xml_file);
                break;
            }
            default: {
                printf("You don't enter a good value");
            }
        }

    } while (cpt < 2);

    return files_name;
}

int verif_dtd(char* dtd_file) {
    char* verif = strchr(dtd_file, '.');
    if(strcmp(verif,".dtd") == 0) {
        return 1;
    }
    return 0;
}

int verif_xml(char* xml_file) {
    char* verif = strchr(xml_file, '.');
    if(strcmp(verif,".xml") == 0) {
        return 1;
    }
    return 0;
}