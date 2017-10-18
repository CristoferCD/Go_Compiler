//
// Created by crist on 18/10/17.
//

#include <stdio.h>
#include "analizadorSintactico.h"
#include "analizadorLexico.h"

void analyze() {
    for(int i = 20; i > 0; i--) {
        node nextComp = next_component();
        printf("%s\n", node_getKey(&nextComp));
    }
}