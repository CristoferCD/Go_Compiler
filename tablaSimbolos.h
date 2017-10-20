//
// Created by crist on 18/10/17.
//

typedef struct tableNode* node;

void symbolTable_init();
void node_create(node* newNode);
char* node_getKey(node* element);
void node_setKey(node* element, char* key);
int node_getId(node* element);
void node_setId(node* element, int id);
void symbolTable_insert(node element);
short symbolTable_search(char* key);
void symbolTable_print();
void symbolTable_free();