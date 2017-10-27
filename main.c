#include <stdio.h>
#include "tablaSimbolos.h"
#include "analizadorSintactico.h"
#include "sistemaEntrada.h"

int main(int argc, char** argv) {
    symbolTable_init();
    inputSys_init();
    //printf("--------------SYMBOL TABLE-------------\n");
    //symbolTable_print();
    printf("-------------ANALYSIS------------------\n");
    analyze();
    //printf("---------------FINAL SYMBOL TABLE-----------\n");
    //symbolTable_print();
    symbolTable_free();
}