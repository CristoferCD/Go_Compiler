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
int alphanumericItem(char firstChar);
int isComment();
int isString();
int isNumberLiteral(char firstChar) ;
int isDecimal() ;
int isOctal() ;
int isHexadecimal() ;
int isOperator(char nextChar) ;
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
        else if (isalpha(nextChar) || nextChar == '_') return alphanumericItem(nextChar); //Only _ return blankID
        else if (nextChar == ' ' || nextChar == '\n' || nextChar == '\r') return 1;
        else if (nextChar == '/') {
            int foundComponent = isComment();
            if (foundComponent == UNIDENTIFIED) {
                foundComponent = isOperator(nextChar);
                if (foundComponent == UNIDENTIFIED) // Standalone token
                    return nextChar;
            }
            return foundComponent;
        }
        else return isOperator(nextChar);
    }
}

int isNumber(char firstChar) {
    int lexComponent = isNumberLiteral(firstChar);

    if (lexComponent == LIT_INTEGER || lexComponent == LIT_FLOAT) { //Check imaginary
        if (next_char() == 'i')
            return LIT_IMAGINARY;
        else
            undoLastMove();
    } else if (lexComponent == UNIDENTIFIED)
        return firstChar;

    return lexComponent;
}

int isNumberLiteral(char firstChar) {
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
    } else if (firstChar >= '1' && firstChar <= '9') {
        isDecimal(); // q1 -> q1
        char nextChar = next_char();
        if (nextChar == '.') { // q1 -> q5
            nextChar = next_char();
            if (isdigit(nextChar)) { // q5 -> q6
                isDecimal();    // q6 -> q6
                nextChar = next_char();
            }
            if (nextChar == 'e' | 'E') { // q5 | q6 -> q7
                nextChar = next_char();
                if (nextChar == '+' || nextChar == '-') nextChar = next_char();
                if (isdigit(nextChar)) {
                    isDecimal();
                    return LIT_FLOAT;
                } else {
                    error_log("Error parsing float's exponent, expected decimal, found: ", getCurrentLine());
                    return ERROR;
                }
            } else {
                // Number ending in "."
                undoLastMove();
                return LIT_INTEGER;
            }
        } else if (nextChar == 'e' || nextChar == 'E') { // q1 -> q7
            nextChar = next_char();
            if (nextChar == '+' || nextChar == '-') nextChar = next_char();
            if (isdigit(nextChar)) {
                isDecimal();
                return LIT_FLOAT;
            } else {
                error_log("Error parsing float's exponent, expected decimal, found: ", getCurrentLine());
                return ERROR;
            }
        } else { // q1
            undoLastMove();
            return LIT_INTEGER;
        }
        // q10
    } else if (firstChar == '.') {    // If it starts with ".", at least one decimal
        if (isdigit(next_char())) { // q10 -> q6
            isDecimal(); // q6 -> q6
            char nextChar = next_char();
            if (nextChar == 'e' || nextChar == 'E') { // q6 -> q7
                nextChar = next_char();
                if (nextChar == '-' || nextChar == '+') nextChar = next_char();
                if (isdigit(nextChar)) { // q7 | q8 -> q9
                    isDecimal();
                    return LIT_FLOAT;
                } else { //TODO: change error log function
                    error_log("Error parsing float's exponent, expected decimal, found: ", getCurrentLine());
                    return ERROR;
                }
            }
        } else {
            undoLastMove();
            return UNIDENTIFIED;
        }
    }
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

int alphanumericItem(char firstChar) {
    char nextChar = next_char();
    short singleCharToken = 1;
    while (isalnum(nextChar) || nextChar == '_') {
        nextChar = next_char();
        singleCharToken = 0;
    }
    //Discards last character that wasn't alpha
    undoLastMove();
    if (singleCharToken && firstChar == '_') return BLANKID;
    else return ID;
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
    } else {
        // The symbol '/' doesn't start a comment
        undoLastMove();
        return UNIDENTIFIED;
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

int isOperator(char nextChar) {
    char secondChar = next_char();
    switch (nextChar) {
        case '+':
            if (secondChar == '=') return OP_PLUSEQ;
            else if (secondChar == '+') return OP_PLUSPLUS;
            break;
        case '&':
            if (secondChar == '=') return OP_AMPEQ;
            else if (secondChar == '&') return OP_AMPAMP;
            else if (secondChar == '^') {
                if (next_char() == '=') {
                    return OP_AMPEXPEQ;
                } else {
                    undoLastMove();
                    return OP_AMPEXP;
                }
            }
            break;
        case '=':
            if (secondChar == '=') return OP_EQEQ;
            break;
        case '!':
            if (secondChar == '=') return OP_NEQ;
            break;
        case '-':
            if (secondChar == '=') return OP_SUBEQ;
            else if (secondChar == '-') return OP_SUBSUB;
            break;
        case '|':
            if (secondChar == '=') return OP_OREQ;
            else if (secondChar == '|') return OP_OROR;
            break;
        case '<':
            if (secondChar == '=') return OP_LEQ;
            else if (secondChar == '<') {
                if (next_char() == '=') {
                    return OP_LESSLESSEQ;
                } else {
                    undoLastMove();
                    return OP_LESSLESS;
                }
            } else if (secondChar == '-') return OP_LEFTARROW;
            break;
        case '*':
            if (secondChar == '=') return OP_MULTEQ;
            break;
        case '^':
            if (secondChar == '=') return OP_EXPEQ;
            break;
        case '>':
            if (secondChar == '=') return OP_MEQ;
            else if (secondChar == '>')
                if (next_char() == '=') {
                    return OP_MOREMOREEQ;
                } else {
                    undoLastMove();
                    return OP_MOREMORE;
                }
            break;
        case '/':
            if (secondChar == '=') return OP_FORWARDSLASHEQ;
            break;
        case ':':
            if (secondChar == '=') return OP_COLONEQ;
            break;
        case '%':
            if (secondChar == '=') return OP_PERCENTAGEEQ;
            break;
        case '.':
            if (secondChar == '.') {
                if (next_char() == '.') return OP_DOTS;
                else undoLastMove();
            }
            break;
        default:
            undoLastMove();
            return nextChar;
    }
    undoLastMove();
    return nextChar;
}