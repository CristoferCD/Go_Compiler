//
// Created by crist on 18/10/17.
//

#include <stdio.h>
#include <ctype.h>
#include "analizadorLexico.h"
#include "sistemaEntrada.h"
#include "tablaSimbolos.h"
#include "definiciones.h"
#include "gestorErrores.h"

int init_Automata ();

node next_component() {
    node nextComp;
    node_create(&nextComp);
    char* lexema;

    int lexComponent = init_Automata();

    lexema = input_Sys_getComponent();

    /**
     * if (id == ID)
     *      buscar o insertar en TS
     **/


    node_setId(&nextComp, lexComponent);
    node_setKey(&nextComp, lexema);
    return nextComp;
}

int init_Automata () {
    while(1) {
        char nextChar = next_char();
        if (nextChar == EOF) return nextChar;
        else if (nextChar == '"') return isString();
        else if (isalpha(nextChar) || nextChar == '_') return alphanumericItem();
        else if (nextChar == ' ' || nextChar == '\n' || nextChar == '\r') return 1;
        else if (nextChar == '/') return isComment();
        else return 42;
    }
}

int alphanumericItem() {
    char nextChar = next_char();
    while (isalnum(nextChar) || nextChar == '_') {
        nextChar = next_char();
    }
    //Discards last character that wasn't alpha
    undoLastMove();

    return ID;
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
                return ERROR;
            }
        }
    }
}

int isString() {
    char nextChar = next_char();
    while(nextChar != '"') {
        nextChar = next_char();
        if (nextChar == '\\') {
            nextChar = next_char();
            if (nextChar == '"') {
                nextChar = next_char();
            } else if (nextChar == 'r' || nextChar == 'n' || nextChar == EOF) {
                error_log("[LEX] Error analyzing string, Not closed\n", getCurrentLine());
                return ERROR;
            }
        } else if (nextChar == '\r' || nextChar == '\n' || nextChar == EOF) {
            error_log("[LEX] Error analyzing string, Not closed\n", getCurrentLine());
            return ERROR;
        }
    }
    return STRING;
}