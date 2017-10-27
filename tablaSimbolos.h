
typedef struct itemNode* node;

void symbolTable_init();
void node_create(node* newNode);
char* node_getKey(node* element);
void node_setKey(node* element, char* key);
int node_getId(node* element);
void node_setId(node* element, int id);
void symbolTable_insert(node element);
int symbolTable_getComponent(char* key);
void symbolTable_print();
void symbolTable_free();