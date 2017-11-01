/**
 * Opens file to parse and initializes first block of memory.
 */
void inputSys_init();

/**
 * Get next character from file and move forward.
 * @return Next character from file.
 */
char next_char();

/**
 * Gets the string between the last one read and the current character.
 * @return A copy of the aforementioned string.
 */
char* input_Sys_getComponent();

/**
 * Gets the count of line breaks since the beginning of the file.
 * @return Current amount of lines read.
 */
int getCurrentLine();

/**
 * Decreases the current character pointer by one position.
 */
void undoLastMove();