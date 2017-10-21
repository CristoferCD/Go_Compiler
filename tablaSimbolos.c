//
// Created by crist on 18/10/17.
//

#include <stdlib.h>
#include <string.h>
#include "tablaSimbolos.h"

struct tableNode {
    int id;
    char* key;
};

typedef struct tableNode* node;

char* node_getKey(node* element);
void node_setKey(node* element, char* key);
int node_getId(node* element);
void node_setId(node* element, int id);

void node_create(node* newNode){
    *newNode = (struct tableNode*)malloc(sizeof(struct tableNode));
}

char* node_getKey(node* element) {
    return (*element)->key;
}

void node_setKey(node* element, char* key) {
    (*element)->key = key;
}

int node_getId(node* element) {
    return (*element)->id;
}

void node_setId(node* element, int id) {
    (*element)->id = id;
}

