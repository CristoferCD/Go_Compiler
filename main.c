//
// Created by crist on 18/10/17.
//

#include "tablaSimbolos.h"
#include "analizadorSintactico.h"
#include "sistemaEntrada.h"

int main(int argc, char** argv) {
    symbolTable_init();
    inputSys_init();
    analyze();
}