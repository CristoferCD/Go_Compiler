
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sistemaEntrada.h"
#include "gestorErrores.h"

#define BLOCK_SIZE 32

char bloqueA[BLOCK_SIZE];
char bloqueB[BLOCK_SIZE];
char* inicio;
char* delantero;
FILE* file;
unsigned int currentLine = 0;
char blockAlreadyRead = 0;

int getComponentSize() {
    char* inicioAux = inicio;
    char* delanteroAux = delantero;
    unsigned int size = 0;
    while (inicioAux != delanteroAux) {
        if (*inicioAux == EOF) return -1;
        inicioAux++;
        size++;
    }
    return size;
}

void inputSys_init() {
    file = fopen("../source/concurrentSum.go", "rb");

    if (file == NULL) {
        error_log("Error opening file\n", 0);
        exit(11);
    }

    size_t sizeRead = fread(bloqueA, sizeof(char), BLOCK_SIZE-1, file);
    if (sizeRead < (BLOCK_SIZE-1)) bloqueA[sizeRead] = EOF;
    bloqueA[BLOCK_SIZE-1] = EOF;
    bloqueB[BLOCK_SIZE-1] = EOF;

    inicio = bloqueA;
    delantero = bloqueA;
}

void inputSys_dispose() {
    fclose(file);
}

char next_char() {
    char newChar = *delantero;

    if (newChar == '\n') currentLine++;
    //TODO: check if lex is bigger than buffer size
    if (newChar == EOF) {
        if (delantero == &bloqueA[BLOCK_SIZE-1]) {
            if (!blockAlreadyRead) {
                size_t totalRead = fread(bloqueB, sizeof(char), BLOCK_SIZE - 1, file);
                if (totalRead < (BLOCK_SIZE - 1)) bloqueB[totalRead] = EOF;
            } else {
                blockAlreadyRead = 0;
            }
            delantero = bloqueB;
            newChar = *delantero;
        } else if (delantero == &bloqueB[BLOCK_SIZE-1]) {
            if (!blockAlreadyRead) {
                size_t totalRead = fread(bloqueA, sizeof(char), BLOCK_SIZE - 1, file);
                if (totalRead < (BLOCK_SIZE - 1)) bloqueA[totalRead] = EOF;
            } else {
                blockAlreadyRead = 0;
            }
            delantero = bloqueA;
            newChar = *delantero;
        } else
            inputSys_dispose();
    } else
        delantero++;
    return newChar;
}

char* getPartialComponent() {
    char* inicioAux = inicio;
    unsigned int size = 0;

    //Get part in first block
    while (*inicioAux != EOF) {
        inicioAux++;
        size++;
    }
    char* firstPart = malloc(size);
    strncpy(firstPart, inicio, size);

    //Change to the other block
    if (inicioAux == &bloqueA[BLOCK_SIZE-1])
        inicioAux = bloqueB;
    else if (inicioAux == &bloqueB[BLOCK_SIZE-1])
        inicioAux = bloqueA;
    else
        error_log("[INPUT_SYS] Error changing block", 0);

    //Get second part
    char* secondAux = inicioAux;
    unsigned int size1 = 0;
    while(secondAux != delantero) {
        secondAux++;
        size1++;
    }
    // Generate full component
    char* component = malloc(size+size1);
    strncpy(component, firstPart, size);
    strncat(component, inicioAux, size1);

    return component;
}

char* input_Sys_getComponent() {
    int componentSize = getComponentSize();
    //If component is between both blocks, concatenate
    char* currentComponent;
    if (componentSize == -1) {
        currentComponent = getPartialComponent();
    } else {
        currentComponent = malloc((size_t) componentSize);
        strncpy(currentComponent, inicio, (size_t) componentSize);
    }
    inicio = delantero;
    return currentComponent;
}

int getCurrentLine() {
    return currentLine;
}

void undoLastMove() {
    //TODO: if there is a block change, the next block is overwritten.
    if (delantero == &bloqueA[0]) {
        delantero = &bloqueB[BLOCK_SIZE - 2];
        blockAlreadyRead = 1;
    } else if (delantero == &bloqueB[0]) {
        delantero = &bloqueA[BLOCK_SIZE - 2];
        blockAlreadyRead = 1;
    } else
        delantero--;
}
