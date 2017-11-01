#include <stdio.h>
#include "analizadorSintactico.h"
#include "analizadorLexico.h"
#include "definiciones.h"

void analyze() {
    node nextComp = next_component();
    while(node_getId(&nextComp) != EOF){
        if (node_getId(&nextComp) != 1 && node_getId(&nextComp) != LINEBREAK)
            printf("[%d]      %s\n", node_getId(&nextComp), node_getKey(&nextComp));
        nextComp = next_component();
    }
}