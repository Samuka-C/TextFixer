#ifndef STRING_OP_LIB
#define STRING_OP_LIB

#include "../string list/string_list.h"

/// @brief A combo with a list of words and a array of integers which represent the amount of that word in a text
typedef struct word_amount_struct
{
    /// @brief List of unique words of a text
    string_list* unique_words;

    /// @brief Array of int which represent the amount of that unique word in a text
    int* amounts;
} words_amount;

/**
 * Returns the entry string without line breaks
 */
char* removeLineBreak(const char* string, int string_size);

/// @brief replaces all non-letter characters with space
/// @param string the original string
/// @return the same pointer to the string
char* filterOnlyLetters(char* string);

/// @brief separates a string into words
/// @param string the string to separate into words
/// @return a string_list with all the words, NULL if it fails to allocate space for the word buffer
string_list* separateStringIntoWords(const char* string);

/// @brief Counts the amount of words from a list of words
/// @param words list of words
/// @return a word_amount with a string_list and a array of int, or a {NULL, NULL} if it fails to allocate space for the amount array
words_amount countWords(string_list* words);

/// @brief Generates a simple graph of the amount of words 
/// @param word_amount a word_amount struct that comes with a list of unique words and a array of amounts
/// @return a string of the graph or NULL if it fails to allocate memory for the graph string
char* graphWordCount(words_amount amount_of_words);

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
