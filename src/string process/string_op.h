#ifndef STRING_OP_LIB
#define STRING_OP_LIB

#include "../string list/string_list.h"

/**
 * Returns the entry string without line breaks
 */
char* removeLineBreak(const char* string, int string_size);

/**
 * Returns a list of words from a string
 */
string_list* separateStringIntoWords(const char* string, int length);

/**
 * Returns 1 if the list of words can be separated into lines of certain length.
 * Returns 0 otherwise.
 * Returns 1 if the list is empty
 * If the pointer is null, it returns -1.
 */
int checkCanSeparate(string_list* stringList, int line_length);

/**
 * Returns a array of numbers in which the first is the number of lines,
 * and the others are the number of words in each line
 * 
 * This assumes the list can be separated (checkCanSeparate returned 1)
 * 
 * E.G. [3, 5, 7, 8] : 3 lines, 5 words in the first line, 7 words in the second line and 8 words in the third line
 * 
 * If the pointer is null, it returns NULL.
 * If the list is empty it will return a pointer to [0]
 */
int* getNumWordsPerLine(string_list* stringList, int line_length);

/**
 * Gets a set of words that fit in a single line of determined size and returns a string of that line
 * 
 * Aligns all words to the left
 */
char* alignLineLeft(string_list* stringList, int line_length);

/**
 * Gets a string and breakes it into lines of determined length
 * 
 * Aligns all words to the left
 * 
 * If its not possible to separate into lines of the determined length, it returns NULL.
 */
char* alignLeft(const char* string, int line_length);

/**
 * Gets a set of words that fit in a single line of determined size and returns a string of that line
 * 
 * Aligns all words to the right
 */
char* alignLineRight(string_list* stringList, int line_length);

/**
 * Gets a string and breakes it into lines of determined length
 * 
 * Aligns all words to the right
 * 
 * If its not possible to separate into lines of the determined length, it returns NULL.
 */
char* alignRight(const char* string, int line_length);

/**
 * Gets a set of words that fit in a single line of determined size and returns a string of that line
 * 
 * Aligns all words to the center
 */
char* alignLineCenter(string_list* stringList, int line_length);

/**
 * Gets a string and breakes it into lines of determined length
 * 
 * Aligns all words to the center
 * 
 * If its not possible to separate into lines of the determined length, it returns NULL.
 */
char* alignCenter(const char* string, int line_length);

/**
 * Gets a set of words that fit in a single line of determined size and returns a string of that line
 * 
 * Aligns all words fix the whole line
 */
char* alignLineJustify(string_list* stringList, int line_length);

/**
 * Gets a string and breakes it into lines of determined length
 * 
 * Aligns all words fix the whole line
 * 
 * If its not possible to separate into lines of the determined length, it returns NULL.
 */
char* alignJustify(const char* string, int line_length);

#endif