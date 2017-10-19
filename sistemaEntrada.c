//
// Created by crist on 18/10/17.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sistemaEntrada.h"

#define BLOCK_SIZE 64

char bloqueA[BLOCK_SIZE];
char bloqueB[BLOCK_SIZE];
char* inicio;
char* delantero;
FILE* file;

unsigned int getComponentSize() {
    char* inicioAux = inicio;
    char* delanteroAux = delantero;
    unsigned int size = 0;
    while (inicioAux != delanteroAux) {
        inicioAux++;
        size++;
    }
    return size;
}

void inputSys_init() {
    file = fopen("../source/concurrentSum.go", "rb");
    fread(bloqueA, sizeof(char), BLOCK_SIZE-1, file);
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
    if (newChar == EOF) {
        if (delantero == &bloqueA[BLOCK_SIZE-1]) {
            fread(bloqueB, sizeof(char), BLOCK_SIZE-1, file);
            delantero = bloqueB;
            newChar = *delantero;
        } else if (delantero == &bloqueB[BLOCK_SIZE-1]) {
            fread(bloqueA, sizeof(char), BLOCK_SIZE-1, file);
            delantero = bloqueA;
            newChar = *delantero;
        } else
            inputSys_dispose();
    } else
        delantero++;
    //TODO: si el lexema queda a medias?
    return newChar;
}

char* input_Sys_getComponent() {
    size_t componentSize = getComponentSize();
    char* currentComponent = malloc(componentSize);
    strncpy(currentComponent, inicio, componentSize);
    inicio = delantero;
    return currentComponent;
}