//
// Created by crist on 18/10/17.
//

#include <stdlib.h>
#include "analizadorLexico.h"
#include "tablaSimbolos.h"

node next_component() {
    node nextComp;
    node_create(&nextComp);
    node_setKey(&nextComp, "componenenet");
    return nextComp;
}