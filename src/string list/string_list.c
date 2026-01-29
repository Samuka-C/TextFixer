#include "string_list.h"

#include <stdlib.h>
#include <stdio.h>
#include "../debug/debug.h"
#include "../string basic/string_basic.h"

struct string_list_link_struct
{
    int string_size;
    char* string;
    struct string_list_link_struct* next_link;
};

struct string_list_struct
{
    string_list_link* first;
};

string_list* strLst_Create()
{
    string_list* newStringList = (string_list*)malloc(sizeof(string_list));
    if (newStringList == NULL)
    {
        logError("error at allocation of new string list");
        return NULL;
    }

    newStringList -> first = NULL;
    return newStringList;
}

int strLst_CheckEmpty(string_list* stringList)
{
    if (stringList == NULL)
    {
        logError("null pointer");
        return -1;
    }

    return (stringList -> first == NULL);
}

int strLst_GetSize(string_list* stringList)
{
    if (stringList == NULL)
    {
        logError("null pointer");
        return -1;
    }

    if (strLst_CheckEmpty(stringList)) return 0;

    int count = 0;
    string_list_link* aux = stringList -> first;

    while (aux != NULL)
    {
        aux = aux -> next_link;
        count++;
    }
    return count;
}

string_list_link* strLst_GetFirstLink(string_list* stringList)
{
    if (stringList == NULL)
    {
        logError("null pointer");
        return NULL;
    }

    if (strLst_CheckEmpty(stringList))
    {
        logWarning("trying to read from empty list");
        return NULL;
    }

    return stringList -> first;
}

string_list_link* strLst_GetLink(string_list* stringList, int index)
{
    if (stringList == NULL)
    {
        logError("null pointer");
        return NULL;
    }

    if (strLst_CheckEmpty(stringList))
    {
        logWarning("trying to read from empty list");
        return NULL;
    }

    if (index < 0) logWarning("negative index");

    if (index <= 0) return stringList -> first;

    int count = 0;
    string_list_link* aux = stringList -> first;

    while (aux -> next_link != NULL && count < index) 
    {
        aux = aux -> next_link;
        count++;
    }

    if (count < index) logWarning("index greater than list size");

    return aux;
}

string_list_link* strLst_GetLastLink(string_list* stringList)
{
    if (stringList == NULL)
    {
        logError("null pointer");
        return NULL;
    }

    if (strLst_CheckEmpty(stringList))
    {
        logWarning("trying to read from empty list");
        return NULL;
    }

    string_list_link* aux = stringList -> first;
    while (aux -> next_link != NULL) aux = aux -> next_link;
    return aux;
}

string_list_link* strLst_GetNextLink(string_list_link* link)
{
    if (link == NULL)
    {
        logError("null pointer");
        return NULL;
    }

    return link -> next_link;
}

int strLst_IsLastLink(string_list_link* link)
{
    if (link == NULL)
    {
        logError("null pointer");
        return -1;
    }

    return link -> next_link == NULL;
}

char* strLst_GetString(string_list_link* link)
{
    if (link == NULL)
    {
        logError("null pointer");
        return NULL;
    }

    return link -> string;
}

int strLst_GetStringSize(string_list_link* link)
{
    if (link == NULL)
    {
        logError("null pointer");
        return -1;
    }

    return link -> string_size;
}

void strLst_Print(string_list* stringList)
{
    int len = strLst_GetSize(stringList);

    for(int index = 0; index < len; index++)
    {
        string_list_link* link = strLst_GetLink(stringList, index);
        if (index > 0) printf(", ");
        printf("%s", link -> string);
    }
    printf("\n");
}

string_list_link* strLst_Append(string_list* stringList, const char* string)
{
    if (stringList == NULL)
    {
        logError("null pointer");
        return NULL;
    }

    string_list_link* new_link = (string_list_link*)malloc(sizeof(string_list_link));
    if (new_link == NULL) 
    {
        logError("error at allocation of new list link");
        return NULL;
    }

    new_link -> string_size = Size(string);
    new_link -> string = Copy(string, new_link -> string_size);
    if (new_link -> string == NULL)
    {
        logError("Can't add new link since string allocation failed");
        free(new_link);
        return NULL;
    }

    new_link -> next_link = NULL;

    if (strLst_CheckEmpty(stringList))
        stringList -> first = new_link;
    else 
        strLst_GetLastLink(stringList) -> next_link = new_link;

    return new_link;
}

string_list_link* strLst_AppendAt(string_list* stringList, const char* string, int index)
{
    if (stringList == NULL)
    {
        logError("null pointer");
        return NULL;
    }

    string_list_link* new_link = (string_list_link*)malloc(sizeof(string_list_link));
    if (new_link == NULL) 
    {
        logError("error at allocation");
        return NULL;
    }

    new_link -> string_size = Size(string);
    new_link -> string = Copy(string, new_link -> string_size);
    if (new_link -> string == NULL)
    {
        logError("Can't add new link since string allocation failed");
        free(new_link);
        return NULL;
    }

    new_link -> next_link = NULL;

    if (strLst_CheckEmpty(stringList))
    {
        stringList -> first = new_link;
        return new_link;
    }

    if (index < 0) logWarning("negative index");

    if (index <= 0)
    {
        string_list_link* aux = stringList -> first;
        stringList -> first = new_link;
        new_link -> next_link = aux;
        return new_link;
    }

    int count = 0;
    string_list_link* previous = NULL;
    string_list_link* aux = stringList -> first;

    while (aux -> next_link != NULL && count < index)
    {
        previous = aux;
        aux = aux -> next_link;
        count++;
    }

    if (count < index) logWarning("index greater than list size");

    previous -> next_link = new_link;
    new_link -> next_link = aux;

    return new_link;
}

void strLst_Remove(string_list* stringList)
{
    if (stringList == NULL)
    {
        logError("null pointer");
        return;
    }

    if (strLst_CheckEmpty(stringList))
    {
        logWarning("trying to remove from empty list");
        return;
    }

    string_list_link* previous = NULL;
    string_list_link* aux = stringList -> first;

    while(aux -> next_link != NULL)
    {
        previous = aux;
        aux = aux -> next_link;
    }

    free(aux -> string);
    free(aux);

    if (previous != NULL) previous -> next_link = NULL;
    else stringList -> first = NULL;
}

void strLst_RemoveAt(string_list* stringList, int index)
{
    if (stringList == NULL)
    {
        logError("null pointer");
        return;
    }

    if (strLst_CheckEmpty(stringList))
    {
        logWarning("trying to remove from empty list");
        return;
    }

    if (index < 0) logWarning("negative index");

    if (index <= 0)
    {
        string_list_link* aux = stringList -> first;
        stringList -> first = aux -> next_link;
        free(aux -> string);
        free(aux);
        return;
    }

    int count = 0;
    string_list_link* previous = NULL;
    string_list_link* aux = stringList -> first;

    while (aux -> next_link != NULL && count < index)
    {
        previous = aux;
        aux = aux -> next_link;
        count++;
    }

    if (count < index) logWarning("index greater than list size");

    if (previous != NULL) 
        previous -> next_link = aux -> next_link;
    else
        stringList -> first = NULL;

    free(aux -> string);
    free(aux);
}


void strLst_Destroy(string_list* stringList)
{
    if (stringList == NULL)
    {
        logError("null pointer");
        return;
    }

    while (!strLst_CheckEmpty(stringList)) strLst_Remove(stringList);

    free(stringList);
}
