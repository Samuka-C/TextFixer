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

            if (character == '\0')
            {
                logWarning("length provided is greater than string actual size");
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

