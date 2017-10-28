#include <stdio.h>
#include <ctype.h>
#include "analizadorLexico.h"
#include "sistemaEntrada.h"
#include "definiciones.h"
#include "gestorErrores.h"
#include "tablaSimbolos.h"

////////////////////////
// Function Declarations
int init_Automata ();
int isNumber(char firstChar);
int alphanumericItem();
int isComment();
int isString();
int isIntegerLiteral(char firstChar) ;
int isDecimal() ;
int isOctal() ;
int isHexadecimal() ;
////////////////////////

node next_component() {
    node nextComp;
    node_create(&nextComp);
    char* lexema;

    int lexComponent = init_Automata();

    lexema = input_Sys_getComponent();

    node_setId(&nextComp, lexComponent);
    node_setKey(&nextComp, lexema);

    if (lexComponent == ID) {
        int componentFoundInTable = symbolTable_getComponent(lexema);
        if (componentFoundInTable == ERROR)
            symbolTable_insert(nextComp);
        else
            node_setId(&nextComp, componentFoundInTable);
    } else if (lexComponent == COMMENT)     // Comments are not forwarded to syntax analyzer.
        return next_component();


    return nextComp;
}

int init_Automata () {
    while(1) {
        char nextChar = next_char();
        if (nextChar == EOF) return nextChar;
        else if (isdigit(nextChar) || nextChar == '.') return isNumber(nextChar);
        else if (nextChar == '"') return isString();
        else if (isalpha(nextChar) || nextChar == '_') return alphanumericItem(); //Only _ return blankID
        else if (nextChar == ' ' || nextChar == '\n' || nextChar == '\r') return 1;
        else if (nextChar == '/') return isComment();
        else return 42;
    }
}

int isNumber(char firstChar) {

    // Do this last, as it's smaller
    int lexComponent = isIntegerLiteral(firstChar);
    /**
     * Try integer
     *      - decimal (all is digit)
     *      - octal (starting with 0, all 0...7)
     *      - hex (0x and at least one hex digit)
     * Try float
     *      -
     * Try imaginary
     *      - decimals or float ending with "i"
     */
    return lexComponent;
}

int isIntegerLiteral(char firstChar) {
    if (firstChar == '0') {
        char nextChar = next_char();
        if (nextChar == 'x' || nextChar == 'X')
            return isHexadecimal();
        else if (nextChar >= '0' && nextChar <= '7')
            return isOctal();
        else {
            undoLastMove();
            return isDecimal();    // Can be a decimal starting by 0 or just a 0 with an ending character like ; or \n
        }
    } else if (firstChar >= '1' && firstChar <= '9')
        return isDecimal();
}

int isDecimal() {
    char nextChar = next_char();
    while (isdigit(nextChar))
        nextChar = next_char();
    undoLastMove();
    return LIT_INTEGER;
}

int isOctal() {
    char nextChar = next_char();
    while (nextChar >= '0' && nextChar <= '7')
        nextChar = next_char();
    undoLastMove();
    return LIT_OCTAL;
}

int isHexadecimal() {
    char nextChar = next_char();
    while (isdigit(nextChar) || (nextChar >= 'a' && nextChar <= 'f') || (nextChar >= 'A' && nextChar <= 'F'))
        nextChar = next_char();
    undoLastMove();
    return LIT_HEXADECIMAL;
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
    return LIT_STRING;
}