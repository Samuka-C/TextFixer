#include "string_op.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../debug/debug.h"
#include "../string list/string_list.h"
#include "../string basic/string_basic.h"

char* removeLineBreak(const char* string, int string_size)
{
    char* new_string = (char*)malloc(string_size + 1);

    int new_string_index = 0;
    for (int string_index = 0; string_index < string_size; string_index++)
    {
        char character = string[string_index];
        if (character != '\n')
        {
            new_string[new_string_index] = character;
            new_string_index++;
        }
        else
        {
            new_string[new_string_index] = ' ';
            new_string_index++;
        }
    }

    new_string[new_string_index] = '\0';

    return new_string;
}

char* filterOnlyLetters(char* string)
{
    int index = 0;
    char character = string[index];

    while (character != '\0')
    {
        if (character < 'A')
            string[index] = ' ';

        if (character > 'Z' && character < 'a')
            string[index] = ' ';

        if (character > 'z')
            string[index] = ' ';

        index++;
        character = string[index];
    }

    return string;
}

string_list* separateStringIntoWords(const char* string)
{
    string_list* words = strLst_Create();
    int buffer_max_size = Size(string) + 1; // If the string is only one word (no spaces) the buffer will have to have the size of the string
                                            // plus the extra \0 char in the end.

    char* buffer = (char*)malloc((buffer_max_size) * sizeof(char));
    if (buffer == NULL)
    {
        logError("error at allocating space for the buffer of words!");
        return NULL;
    }
    int buffer_size = 0;

    int index = 0;
    char character = string[index];

    while (character != '\0')
    {
        if (character == ' ' || character == '\t' || character == '\n')
        {
            if (buffer_size > 0)
            {
                char* word = Copy(buffer, buffer_size);
                strLst_Append(words, word);
                free(word);
                buffer_size = 0;
            }
        }
        else
        {
            buffer[buffer_size] = character;
            buffer_size++;
        }

        index++;
        character = string[index];
    }

    if (buffer_size > 0)
    {
        char* word = Copy(buffer, buffer_size);
        strLst_Append(words, word);
        free(word);
        buffer_size = 0;
    }

    free(buffer);
    return words;
}

/// @brief Gets the size of the biggest word of a list
/// @param word_list list of words to look through
/// @return the size of the longest word
int getBiggestWord(string_list* word_list)
{
    int largest_word_length = 0;

    for (int index = 0; index < strLst_GetSize(word_list); index++)
    {
        int word_length = strLst_GetStringSize(strLst_GetLink(word_list, index));
        largest_word_length = word_length > largest_word_length ? word_length : largest_word_length;
    }

    return largest_word_length;
}

/// @brief Checks if a word is present in a list of words
/// @param new_word word to check if equal
/// @param words list of words
/// @return the index of that word in the list if the word belongs to the list, -1 if it doesn't belong to the list
int compareMultiple(const char* new_word, string_list* words)
{
    for (int index = 0; index < strLst_GetSize(words); index++)
    {
        char* word = strLst_GetString(strLst_GetLink(words, index));
        if (Compare(word, new_word))
            return index;
    }

    return -1;
}

words_amount countWords(string_list* words)
{
    int number_words = strLst_GetSize(words);

    string_list* unique_words = strLst_Create();
    int* amounts = (int*)calloc(number_words, sizeof(int));
    if (amounts == NULL)
    {
        logError("error at allocating memory for the int array!");
        return (words_amount){NULL, NULL};
    }

    for (int index = 0; index < number_words; index++)
    {
        char* word = strLst_GetString(strLst_GetLink(words, index));
        logDebug("word to check: %s", word);

        int unique_word_index = compareMultiple(word, unique_words);

        if (unique_word_index >= 0) 
        {
            logDebug("that word was repeated!");
            amounts[unique_word_index]++;
            logDebug("now there are %d of the word \"%s\"", amounts[unique_word_index], strLst_GetString(strLst_GetLink(unique_words, unique_word_index)));
        }
        else
        {
            logDebug("the word \"%s\" is unique! and now there is 1 of them!", word);
            strLst_Append(unique_words, word);
            amounts[strLst_GetSize(unique_words) - 1] = 1;
        }
    }

    return (words_amount){unique_words, amounts};
}

char* graphWordCount(words_amount amount_of_words)
{
    string_list* unique_words = amount_of_words.unique_words;
    int* amounts = amount_of_words.amounts;
    int number_unique_words = strLst_GetSize(unique_words);

    int total_number_words = 0;
    int largest_amount = 0;
    for (int amount_index = 0; amount_index < number_unique_words; amount_index++)
    {
        int amount = amounts[amount_index];
        total_number_words += amount;
        largest_amount = amount > largest_amount ? amount : largest_amount;
    }

    logDebug("largest amount of words: %d", largest_amount);
    logDebug("total number of words: %d", total_number_words);
    if (total_number_words == 0)
        return "NO WORDS!!";

    int largest_word_length = getBiggestWord(unique_words);
    int largest_amount_length = 0;
    for (int amount_index = 0; amount_index < number_unique_words; amount_index++)
    {
        int n = amounts[amount_index];
        int length = (n == 0) ? 1 : (int)floor(log10(abs(n))) + 1;
        largest_amount_length = length > largest_amount_length ? length : largest_amount_length;
    }

    logDebug("largest_word_length: %d", largest_word_length);
    logDebug("largest_amount_length: %d", largest_amount_length);

    // (largest_word_length + " | " + largest_amount_length + " | " + "000.00%" + " | " + "####################") x number_unique_words

    int line_size = largest_word_length + 3 + largest_amount_length + 3 + 7 + 3 + 10;
    logDebug("line_size: %d", line_size);

    char* graph = (char*)malloc(((line_size + 1) * number_unique_words) * sizeof(char));
    if (graph == NULL)
    {
        logError("error at allocation of memory for the graph string!");
        return NULL;
    }
    graph[0] = '\0';
    
    for (int word_index = 0; word_index < number_unique_words; word_index++)
    {
        char* word = strLst_GetString(strLst_GetLink(unique_words, word_index));
        string_list* single_word_list = strLst_Create();
        strLst_Append(single_word_list, word);
        char* word_aligned_right = alignLineRight(single_word_list, largest_word_length);
        strLst_Destroy(single_word_list);

        logDebug("word_aligned_right: %s", word_aligned_right);

        int amount = amounts[word_index]; 
        logDebug("amount of word: %d", amount);

        char number[largest_amount_length + 1];
        sprintf(number, "%d", amount);
        string_list* single_number_list = strLst_Create();
        strLst_Append(single_number_list, number);
        char* number_aligned_center = alignLineCenter(single_number_list, largest_amount_length);
        strLst_Destroy(single_number_list);

        logDebug("number_aligned_center: %s", number_aligned_center);

        float percentage = (amount * 100 / total_number_words);
        logDebug("percentage: %.2f%%", percentage);

        char percentage_string[8];
        sprintf(percentage_string, "%.2f%%", percentage);
        string_list* single_percentage_list = strLst_Create();
        strLst_Append(single_percentage_list, percentage_string);
        char* percentage_aligned_center = alignLineCenter(single_percentage_list, 7);
        strLst_Destroy(single_percentage_list);

        logDebug("percentage_aligned_center: %s", percentage_aligned_center);

        int number_of_number_sign = (int)round(amount * 10 / largest_amount);
        logDebug("number of # (%d * 10 / %d) = %d", amount, largest_amount, number_of_number_sign);

        char bar_string[11];
        for (int i = 0; i < 10; i++)
            bar_string[i] = i < number_of_number_sign ? '#' : ' ';
        bar_string[10] = '\0';

        logDebug("bar_string: %s", bar_string);

        char* line = (char*)malloc((line_size + 1) * sizeof(char));
        sprintf(line, "%s | %s | %s | %s", word_aligned_right, number_aligned_center, percentage_aligned_center, bar_string);
        if (Size(line) > line_size) logWarning("tamanho da linha: %d eh maior que o tamanho maximo da linha: %d", Size(line), line_size);

        logDebug("graph before the line:\n%s", graph);
        logDebug("line: \"%s\"", line);

        free(word_aligned_right);
        free(number_aligned_center);
        free(percentage_aligned_center);

        strcat(graph, line);
        logDebug("graph after the line:\n%s", graph);
        strcat(graph, "\n");

        free(line);
    }

    logDebug("graph in the end:\n%s", graph);

    free(amounts);
    strLst_Destroy(unique_words);

    return graph;
}

int checkCanSeparate(string_list* stringList, int line_length)
{
    if (stringList == NULL)
    {
        logError("null pointer");
        return -1;
    }

    int canRead = !strLst_CheckEmpty(stringList);
    string_list_link* link;

    if (canRead)
        link = strLst_GetFirstLink(stringList);

    while (canRead)
    {
        if (strLst_GetStringSize(link) > line_length)
            return 0;
        
        if (!strLst_IsLastLink(link))
            link = strLst_GetNextLink(link);
        else
            canRead = 0;
    }

    return 1;
}

int* getNumWordsPerLine(string_list* stringList, int line_length)
{
    if (stringList == NULL)
    {
        logError("null pointer");
        return NULL;
    }

    int numWordsTotal = strLst_GetSize(stringList);
    int numWordsPerLineAux[numWordsTotal];
    numWordsPerLineAux[0] = 0; // remove memory garbage from first item of the array
    int numLines = 0;

    logDebug("number of words: %d", numWordsTotal);

    int buffer = 0;

    int canRead = !strLst_CheckEmpty(stringList);
    string_list_link* link;

    if (canRead)
    {
        link = strLst_GetFirstLink(stringList);
        numLines++;
    }

    while (canRead)
    {
        logDebug("buffer: %d", buffer);
        logDebug("number of lines: %d", numLines);
        logDebug("number of words in the last line: %d", numWordsPerLineAux[numLines - 1]);

        char* word = strLst_GetString(link);
        logDebug("word: %s", word);

        int wordSize = strLst_GetStringSize(link);
        logDebug("word len: %d", wordSize);

        if (buffer == 0)
        {
            buffer = wordSize;
            numWordsPerLineAux[numLines - 1]++;
        }
        else if (buffer + wordSize + 1 > line_length)
        {
            numLines++;
            buffer = wordSize;
            numWordsPerLineAux[numLines - 1] = 1; // remove memory garbage from the next item of the array
        }
        else
        {
            buffer += wordSize + 1;
            numWordsPerLineAux[numLines - 1]++;
        }

        if (!strLst_IsLastLink(link))
            link = strLst_GetNextLink(link);
        else
            canRead = 0;
    }

    logDebug("buffer: %d", buffer);
    logDebug("number of lines: %d", numLines);
    logDebug("number of words in the last line: %d", numWordsPerLineAux[numLines - 1]);

    int* numWordsPerLine = (int*)malloc((numLines + 1) * sizeof(int));
    numWordsPerLine[0] = numLines;
    for (int index = 1; index <= numLines; index++)
        numWordsPerLine[index] = numWordsPerLineAux[index - 1];
    
    return numWordsPerLine;
}

typedef char* (*alignLineFunc)(string_list* stringList, int line_length);

char* alignLineLeft(string_list* stringList, int line_length)
{
    char* line = (char*)malloc((line_length + 1) * sizeof(char));
    int index = 0;

    int canRead = !strLst_CheckEmpty(stringList);
    string_list_link* link;

    if (canRead)
        link = strLst_GetFirstLink(stringList);

    while (canRead)
    {
        char* word = strLst_GetString(link);
        int wordSize = strLst_GetStringSize(link);

        for (int index_aux = 0; index_aux < wordSize; index_aux++)
        {
            line[index] = word[index_aux];
            index++;
        }

        if (!strLst_IsLastLink(link))
        {
            link = strLst_GetNextLink(link);
            line[index] = ' ';
            index++;
        }
        else
            canRead = 0;
    }

    line[index] = '\0';

    return line;
}

char* alignLineRight(string_list* stringList, int line_length)
{
    char* line = (char*)malloc((line_length + 1) * sizeof(char));
    int index = 0;

    int totalWordLength = 0;
    int numWords = strLst_GetSize(stringList);
    logDebug("number of words in line: %d", numWords);
    
    string_list_link* link;
    int canRead = !strLst_CheckEmpty(stringList);

    if (canRead)
        link = strLst_GetFirstLink(stringList);
    
    while (canRead)
    {
        int wordLength = strLst_GetStringSize(link);
        totalWordLength += wordLength;

        if (!strLst_IsLastLink(link))
            link = strLst_GetNextLink(link);
        else
            canRead = 0;
    }
    logDebug("total length of all words: %d", totalWordLength);

    int totalSpaces = line_length - totalWordLength;
    int numSeparations = numWords - 1;
    int numSpacesToTheLeft = totalSpaces - numSeparations;

    logDebug("number of spaces to the left: %d", numSpacesToTheLeft);

    for (int i = 0; i < numSpacesToTheLeft; i++)
    {
        line[index] = ' ';
        index++;
    }

    canRead = !strLst_CheckEmpty(stringList);

    if (canRead)
        link = strLst_GetFirstLink(stringList);

    while (canRead)
    {
        char* word = strLst_GetString(link);
        int wordSize = strLst_GetStringSize(link);

        for (int index_aux = 0; index_aux < wordSize; index_aux++)
        {
            line[index] = word[index_aux];
            index++;
        }

        if (!strLst_IsLastLink(link))
        {
            link = strLst_GetNextLink(link);
            line[index] = ' ';
            index++;
        }
        else
            canRead = 0;
    }

    line[index] = '\0';

    return line;
}

char* alignLineCenter(string_list* stringList, int line_length)
{
    char* line = (char*)malloc((line_length + 1) * sizeof(char));
    int index = 0;

    int totalWordLength = 0;
    int numWords = strLst_GetSize(stringList);
    logDebug("number of words in line: %d", numWords);
    
    string_list_link* link;
    int canRead = !strLst_CheckEmpty(stringList);

    if (canRead)
        link = strLst_GetFirstLink(stringList);
    
    while (canRead)
    {
        int wordLength = strLst_GetStringSize(link);
        totalWordLength += wordLength;

        if (!strLst_IsLastLink(link))
            link = strLst_GetNextLink(link);
        else
            canRead = 0;
    }
    logDebug("total length of all words: %d", totalWordLength);

    int totalSpaces = line_length - totalWordLength;
    int numSeparations = numWords - 1;
    int numSpacesOutside = totalSpaces - numSeparations;

    int numSpacesToTheLeft = numSpacesOutside / 2;
    int numSpacesToTheRight = numSpacesOutside / 2 + numSpacesOutside % 2;

    logDebug("number of spaces to the left: %d", numSpacesToTheLeft);
    logDebug("number of spaces to the right: %d", numSpacesToTheRight);

    for (int i = 0; i < numSpacesToTheLeft; i++)
    {
        line[index] = ' ';
        index++;
    }

    canRead = !strLst_CheckEmpty(stringList);

    if (canRead)
        link = strLst_GetFirstLink(stringList);

    while (canRead)
    {
        char* word = strLst_GetString(link);
        int wordSize = strLst_GetStringSize(link);

        for (int index_aux = 0; index_aux < wordSize; index_aux++)
        {
            line[index] = word[index_aux];
            index++;
        }

        if (!strLst_IsLastLink(link))
        {
            link = strLst_GetNextLink(link);
            line[index] = ' ';
            index++;
        }
        else
            canRead = 0;
    }

    for (int i = 0; i < numSpacesToTheRight; i++)
    {
        line[index] = ' ';
        index++;
    }

    line[index] = '\0';

    return line;
}

char* alignLineJustify(string_list* stringList, int line_length)
{
    char* line = (char*)malloc((line_length + 1) * sizeof(char));
    int index = 0;

    int totalWordLength = 0;
    int numWords = strLst_GetSize(stringList);
    logDebug("number of words in line: %d", numWords);
    
    string_list_link* link;
    int canRead = !strLst_CheckEmpty(stringList);

    if (canRead)
        link = strLst_GetFirstLink(stringList);
    
    while (canRead)
    {
        int wordLength = strLst_GetStringSize(link);
        totalWordLength += wordLength;

        if (!strLst_IsLastLink(link))
            link = strLst_GetNextLink(link);
        else
            canRead = 0;
    }
    logDebug("total length of all words: %d", totalWordLength);

    int totalSpaces = line_length - totalWordLength;
    int numSeparations = numWords > 1 ? numWords - 1 : 1;

    logDebug("number of spaces total: %d", totalSpaces);
    logDebug("numSeparations: %d", numSeparations);

    int spaces[numSeparations];
    for (int i = 0; i < numWords - 1; i++)
    {
        spaces[i] = 0;
    }

    while (totalSpaces > 0)
    {
        for (int i = 0; i < numSeparations; i++)
        {
            if (totalSpaces > 0)
            {
                spaces[i]++;
                totalSpaces--;
            }
            else
                break;
        }
    }

    int spacesIndex = 0;

    canRead = !strLst_CheckEmpty(stringList);

    if (canRead)
        link = strLst_GetFirstLink(stringList);

    while (canRead)
    {
        char* word = strLst_GetString(link);
        int wordSize = strLst_GetStringSize(link);

        logDebug("word: %s", word);

        for (int index_aux = 0; index_aux < wordSize; index_aux++)
        {
            line[index] = word[index_aux];
            index++;
        }

        if (!strLst_IsLastLink(link))
        {
            link = strLst_GetNextLink(link);

            logDebug("spaces to add: %d", spaces[spacesIndex]);
            for (int i = 0; i < spaces[spacesIndex]; i++)
            {
                line[index] = ' ';
                index++;
            }
            spacesIndex++;
        }
        else
            canRead = 0;
    }

    line[index] = '\0';

    return line;
}

char* align(alignLineFunc alignLineMethod, const char* string, int line_length)
{
    int stringlength = Size(string);
    logDebug("string length: %d", stringlength);
    string_list* words = separateStringIntoWords(string);

    if (!checkCanSeparate(words, line_length))
    {
        logError("unable to separate string in lines of size %d", line_length);
        return NULL;
    }

    int* numWordsPerLine = getNumWordsPerLine(words, line_length);
    int numberLines = numWordsPerLine[0];
    logDebug("number of lines: %d", numberLines);

    int wordIndex = 0;

    char* alignedString = (char*)malloc(numberLines * (line_length + 1) * sizeof(char));
    int alignedStringIndex = 0;

    for (int lineIndex = 1; lineIndex <= numberLines; lineIndex++)
    {
        int numWordsLine = numWordsPerLine[lineIndex];
        string_list* lineWords = strLst_Create();

        for (int lineWordIndex = 0; lineWordIndex < numWordsLine; lineWordIndex++)
        {
            string_list_link* wordLink = strLst_GetLink(words, wordIndex + lineWordIndex);
            strLst_Append(lineWords, strLst_GetString(wordLink));
        }
        wordIndex += numWordsLine;

        char* line = alignLineMethod(lineWords, line_length);
        int lineSize = Size(line);
        logDebug("line: %s", line);

        for (int index = 0; index < lineSize; index++)
        {
            alignedString[alignedStringIndex] = line[index];
            alignedStringIndex++;
        }

        if (lineIndex != numberLines)
        {
            alignedString[alignedStringIndex] = '\n';
            alignedStringIndex++;
        }

        free(line);
        strLst_Destroy(lineWords);
    }

    strLst_Destroy(words);

    alignedString[alignedStringIndex] = '\0';

    return alignedString;
}

char* alignLeft(const char* string, int line_length)
{
    return align(alignLineLeft, string, line_length);
}

char* alignRight(const char* string, int line_length)
{
    return align(alignLineRight, string, line_length);
}

char* alignCenter(const char* string, int line_length)
{
    return align(alignLineCenter, string, line_length);
}

char* alignJustify(const char* string, int line_length)
{
    return align(alignLineJustify, string, line_length);
}
