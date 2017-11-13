#include <stdio.h>
#include <stdlib.h>
#include "tablaSimbolos.h"
#include "analizadorSintactico.h"
#include "lex/lex.yy.h"

int main(int argc, char** argv) {
    symbolTable_init();
    FILE* file = NULL;
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", argv[1]);
        exit(1);
    }
    yyin = file;
    printf("-------------ANALYSIS------------------\n");
    analyze();
    symbolTable_free();
    fclose(yyin);
}