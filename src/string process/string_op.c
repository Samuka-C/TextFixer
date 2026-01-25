#include "string_op.h"

#include <stdio.h>
#include <stdlib.h>

#include "../debug/debug.h"
#include "../string list/string_list.h"

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
    }

    new_string[new_string_index] = '\0';

    return new_string;
}
