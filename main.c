#include <stdio.h>
#include "tablaSimbolos.h"
#include "analizadorSintactico.h"
#include "lex/lex.yy.h"

int main(int argc, char** argv) {
    symbolTable_init();
    yyin = fopen("../source/concurrentSum.go", "r");
    printf("-------------ANALYSIS------------------\n");
    analyze();
    symbolTable_free();
    fclose(yyin);
}