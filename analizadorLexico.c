#include <stdio.h>
#include <ctype.h>
#include "analizadorLexico.h"
#include "definiciones.h"
#include "gestorErrores.h"
#include "lex/lex.yy.h"

node next_component() {
    node nextComp;
    node_create(&nextComp);

    int lexComponent = yylex();

    node_setId(&nextComp, lexComponent);
    node_setKey(&nextComp, yytext);

    if (lexComponent == ID) {
        int componentFoundInTable = symbolTable_getComponent(yytext);
        if (componentFoundInTable == ERROR)
            symbolTable_insert(nextComp);
        else
            node_setId(&nextComp, componentFoundInTable);
    }

    return nextComp;
}