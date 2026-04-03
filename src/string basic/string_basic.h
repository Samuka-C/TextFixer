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

/// @brief Tells if two strings are the same, value wise
/// @param string_a first string
/// @param string_b second string
/// @return 1 if they are the same, 0 if they are different
int Compare(const char* string_a, const char* string_b);

#endif
