#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "StringLinkedList.h"

#define BUFF_SIZE 1000
#define FIRST_APOS_POS 9
#define INCLUDE "#include"
#define DOUBLE_APOS '"'

int findSecondApos(char s[]) {
    int pos = 0;
    int ctr = 0;
    for(int i = 0; s[i] != '\0'; i++) {
        if(s[i] == '"') {
            if(ctr == 0) {
                ctr++;
            } else {
                return pos;
            }
        } 
        pos++;
    }
}

bool isInclude(char s[]) {
    int secondAposPos = findSecondApos(s);

    for(int i = 0; INCLUDE[i] != '\0'; i++) {
        if(INCLUDE[i] != s[i]) {
            return false;
        }
    }

    if(s[FIRST_APOS_POS] != DOUBLE_APOS && 
       s[secondAposPos] != DOUBLE_APOS)
    {
        return false;
    }
    return true;
}

char* headerFile(char line[]) {
    /* Determine file name */
    int headerFileLength = findSecondApos(line) - FIRST_APOS_POS - 1;
    char* headerFileName_dynamic = calloc(headerFileLength, sizeof(char));

    for(int i = 0; i < headerFileLength; i++) {
        headerFileName_dynamic[i] = line[FIRST_APOS_POS + 1 + i];
    }
    headerFileName_dynamic[headerFileLength] = '\0';

    return headerFileName_dynamic;
    /**/
}

void printHeaderContents(char prevHeaderFileName[], FILE *outputFile, LinkedList* root) {
    /* Initiate header file */
    FILE *inputFile;
    inputFile = fopen(prevHeaderFileName, "r");

    if(inputFile == NULL) {
        perror("Error while opening the file.\n");
        printf("%s\n", prevHeaderFileName);
        exit(EXIT_FAILURE);
    }
    /**/

    /* Print contents */
    char line[BUFF_SIZE];
    while(fgets(line, BUFF_SIZE, inputFile) != NULL) {
        if(isInclude(line)) {
            char* headerFileName = headerFile(line);

            if(!isInsideList(headerFileName, root)) {
                addList(headerFileName, root);
                printHeaderContents(headerFileName, outputFile, root);
                fprintf(outputFile, "\n");             
            }

        } else {
            fprintf(outputFile, "%s", line);
        }
    }
    /**/

    /* Destroy files */
    fclose(inputFile);
    /**/
}

void main() {
    LinkedList root = createList();
    /* Initiate files */
    FILE *inputFile, *outputFile;
    inputFile = fopen("main.c", "r"); 
    outputFile = fopen("output.c", "w");

    if(inputFile == NULL) {
        perror("Error while opening the file.\n");
        printf("main.c");
        exit(EXIT_FAILURE);
    }

    if(outputFile == NULL) {
        perror("Error while opening the file.\n");
        printf("output.c");
        exit(EXIT_FAILURE);
    }

    /**/

    /* Print contents */
    char line[BUFF_SIZE];
    while(fgets(line, BUFF_SIZE, inputFile) != NULL) {
        if(isInclude(line)) {
            char* headerFileName = headerFile(line);

            if(!isInsideList(headerFileName, &root)) {
                addList(headerFileName, &root);
                printHeaderContents(headerFileName, outputFile, &root);
                fprintf(outputFile, "\n");
                fprintf(outputFile, "\n");  
            }
 
        } else {
            fprintf(outputFile, "%s", line);
        }
    }
    /**/

    /* Destroy files */
    fclose(inputFile);
    fclose(outputFile);
    /**/
}