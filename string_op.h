#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

#ifndef STRING_OP_LIB
#define STRING_OP_LIB

/*Retorna o tamanho de uma string*/
int getStringSize(const char* string)
{
    int size = 0;
    while (string[size] != '\0') size++;
    return size;
}

/* Ao receber uma string, deve retornar a mesma string
mas sem nenhuma quebra de linha*/
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

#endif