/**
 * Structure defining a node in the symbol table.
 */
typedef struct itemNode* node;

/**
 * Initializes the data structure and loads Golang's reserved words.
 */
void symbolTable_init();

/**
 * Initializes memory for a node.
 * @param newNode Pointer to the newly allocated memory.
 */
void node_create(node* newNode);

/**
 * Gets string value from this node.
 * @param element Node containing the string.
 * @return String value.
 */
char* node_getKey(node* element);

/**
 * Sets string value to the node structure.
 * @param element Element to host the string.
 * @param key String value to be assigned.
 */
void node_setKey(node* element, char* key);

/**
 * Get lexical component from this node.
 * @param element Node containing the value.
 * @return Lexical component.
 */
int node_getId(node* element);

/**
 * Sets integer value as lexical component for this node.
 * @param element Node to host de value.
 * @param id Value to be assigned.
 */
void node_setId(node* element, int id);

/**
 * Inserts a node inside the symbol table.
 * Duplicated elements can be inserted.
 * @param element Element to be inserted.
 */
void symbolTable_insert(node element);

/**
 * Gets lexical component assigned to a node in the table with
 * the same key as provided.
 * @param key Key to match the node.
 * @return Lexical component of the node matched.
 * @return ERROR when key is not found inside the table.
 */
int symbolTable_getComponent(char* key);

/**
 * Displays on standard output the contents of the symbol table.
 */
void symbolTable_print();

/**
 * Destroy data structure and free allocated memory.
 */
void symbolTable_free();