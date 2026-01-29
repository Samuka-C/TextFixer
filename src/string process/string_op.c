#include "string_op.h"

#include <stdio.h>
#include <stdlib.h>

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

string_list* separateStringIntoWords(const char* string, int length)
{
    string_list* words = strLst_Create();

    char* buffer = (char*)malloc((length+1) * sizeof(char));
    int buffer_size = 0;
    
    for (int index = 0; index <= length; index++)
    {
        char character = string[index];

        if (character == ' ' || character == '\t' || character == '\n' || character == '\0')
        {
            if (buffer_size != 0)
            {
                char* word = Copy(buffer, buffer_size);
                strLst_Append(words, word);
                free(word);
                buffer_size = 0;
            }

            if (character == '\0' && index < length)
            {
                logWarning("length provided is greater than string actual size of the string. (length provided: %d, actual size: %d)", length, index);
                break;
            }
        }
        else
        {
            buffer[buffer_size] = character;
            buffer_size++;
        }
    }

    free(buffer);
    return words;
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
    int numLines = 0;

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
        int wordSize = strLst_GetStringSize(link);

        if (buffer == 0)
        {
            buffer = wordSize;
            numWordsPerLineAux[numLines - 1]++;
        }
        else if (buffer + wordSize + 1 > line_length)
        {
            numLines++;
            buffer = wordSize;
            numWordsPerLineAux[numLines - 1]++;
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

    int* numWordsPerLine = malloc((numLines + 1) * sizeof(int));
    numWordsPerLine[0] = numLines;
    for (int index = 1; index <= numLines; index++)
        numWordsPerLine[index] = numWordsPerLineAux[index - 1];
    
    return numWordsPerLine;
}