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
string_list* separateStringIntoWords(const char* string);

#endif