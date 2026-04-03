#include "string_basic.h"

#include <stdlib.h>
#include "../debug/debug.h"

int Size(const char* string)
{
    int size = 0;
    while (string[size] != '\0') size++;
    return size;
}

char* Copy(const char* string, int size)
{
    if (size < 0)
    {
        logError("size of string can't be negative");
        return NULL;
    }

    char* copy = (char*)malloc((size + 1) * sizeof(char));
    if (copy == NULL)
    {
        logError("error at allocation of new string");
        return NULL;
    }

    int index;
    for(index = 0; index < size; index++) copy[index] = string[index];
    copy[index] = '\0';
    return copy;
}

int Compare(const char* string_a, const char* string_b)
{
    int index = 0;
    while (string_a[index] != '\0' && string_b[index] != '\0')
    {
        if (string_a[index] != string_b[index])
            return 0;

        index++;
    }

    // Check if both are empty when one of them is empty
    if (string_a[index] != string_b[index])
        return 0;

    return 1;
}
