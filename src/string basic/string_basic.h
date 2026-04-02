#ifndef STRING_BASIC
#define STRING_BASIC

/**
 * Returns the size of a string.
 */
int Size(const char* string);

/**
 * Creates a copy of a string.
 * If it fails to allocate memory to the string, it returns NULL.
 * Returns a pointer to the new string.
 */
char* Copy(const char* string, int size);

#endif
