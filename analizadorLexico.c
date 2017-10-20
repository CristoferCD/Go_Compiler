//
// Created by crist on 18/10/17.
//

#include <stdio.h>
#include "analizadorLexico.h"
#include "sistemaEntrada.h"
#include "tablaSimbolos.h"

int init_Automata ();

node next_component() {
    node nextComp;
    node_create(&nextComp);
    char* componente;

    int id = init_Automata();

    //TODO: negative error codes (o dejar que el automata use el logger)

    componente = input_Sys_getComponent();

    /**
     * if (id == ID)
     *      buscar o insertar en TS
     **/


    node_setId(&nextComp, id);
    node_setKey(&nextComp, componente);
    return nextComp;
}

int init_Automata () {
    while(1) {
        char nextChar = next_char();
        if (nextChar == EOF) return nextChar;
        if (nextChar == ' ' || nextChar == '\n') return 1;
    }
}