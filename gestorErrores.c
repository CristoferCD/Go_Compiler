#include <stdio.h>
#include "gestorErrores.h"

void error_log(char* message, int lineNumber) {
    printf("%c[1;31mError [line %d]: %s %c[0;00m\n", 27, lineNumber, message, 27);
}