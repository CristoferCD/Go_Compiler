#include <stdio.h>
#include "gestorErrores.h"

void error_log(char* message, int lineNumber) {
    printf("Error[l. %d]: %s", lineNumber, message);
}