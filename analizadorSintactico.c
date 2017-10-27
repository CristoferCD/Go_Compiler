#include <stdio.h>
#include "analizadorSintactico.h"
#include "analizadorLexico.h"

void analyze() {
    node nextComp = next_component();
    while(node_getId(&nextComp) != EOF){
        if (node_getId(&nextComp) != 1)
            printf("[%d]      %s\n", node_getId(&nextComp), node_getKey(&nextComp));
        nextComp = next_component();
    }
}