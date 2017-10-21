//
// Created by crist on 18/10/17.
//

#include <stdio.h>
#include "analizadorLexico.h"
#include "sistemaEntrada.h"
#include "tablaSimbolos.h"
#include "definiciones.h"
#include "gestorErrores.h"

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
        else if (nextChar == ' ' || nextChar == '\n') return 1;
        else if (nextChar == '/') return isComment();
    }
}

int isComment() {
    char nextChar = next_char();
    int currentLine = getCurrentLine();
    if (nextChar == '/') {
        while (nextChar != '\n')
            nextChar = next_char();
        return COMMENT;
    } else if (nextChar == '*') {
        while (1) {
            nextChar = next_char();
            while (nextChar == '*') {
                nextChar = next_char();
                if (nextChar == '/') return COMMENT;
            }
            if (nextChar == EOF) {
                error_log("[LEX] Error analyzing multiline comment. Not closed\n", currentLine);
                return ERROR_COMMENT;
            }
        }
    }
}