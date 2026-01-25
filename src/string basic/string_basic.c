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