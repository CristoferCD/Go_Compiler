//
// Created by crist on 18/10/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analizadorLexico.h"
#include "sistemaEntrada.h"
#include "tablaSimbolos.h"

int simul_Automata (char item);

node next_component() {
    node nextComp;
    node_create(&nextComp);
    char* componente;
    char nextChar;

    int accepted = 0;
    do {
        nextChar = next_char();
        accepted = simul_Automata(nextChar);
    } while(accepted == 0);

    componente = input_Sys_getComponent();

    node_setKey(&nextComp, componente);
    return nextComp;
}

int simul_Automata (char item) {
    if (item == ' ' || item == '\n' || item == 0 || item == -1)
        return 1;
    else
        return 0;
}