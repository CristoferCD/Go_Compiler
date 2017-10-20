//
// Created by crist on 18/10/17.
//

#include <stdio.h>
#include "analizadorSintactico.h"
#include "analizadorLexico.h"

void analyze() {
    node nextComp = next_component();
    while(node_getId(&nextComp) != EOF){
        printf("%s", node_getKey(&nextComp));
        nextComp = next_component();
    }
}