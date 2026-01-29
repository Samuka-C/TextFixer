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
 */
int checkCanSeparate(string_list* stringList, int line_length);

#endif