#include <stdlib.h>
#include "debug.h"

#ifndef STRING_LIST
#define STRING_LIST

/**
 * Returns the size of a string.
 */
int Size(const char* string)
{
    int size = 0;
    while (string[size] != '\0') size++;
    return size;
}

/**
 * Creates a copy of a string.
 * If it fails to allocate memory to the string, it returns NULL.
 * Returns a pointer to the new string.
 */
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

typedef struct string_list_link_struct
{
    int string_size;
    char* string;
    struct string_list_link_struct* next_link;
} 
string_list_link;

typedef struct string_list_struct
{
    string_list_link* first;
}
string_list;

/**
 * Creates a new empty string list.
 * If it fails to allocate memory for the list, it returns NULL.
 * Returns a pointer to the new list.
 */
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

/**
 * Returns 1 if the list is empty. otherwise it returns 0.
 * If the pointer is null it returns -1 (which still counts as true).
 */
int strLst_CheckEmpty(string_list* stringList)
{
    if (stringList == NULL)
    {
        logError("null pointer");
        return -1;
    }

    return (stringList -> first == NULL);
}

/**
 * Returns the size of a list.
 * If the pointer is null, it returns -1.
 */
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

/**
 * Returns a pointer to the last link of a list.
 * If the pointer is null, it returns NULL.
 * If the list is empty it returns NULL.
 */
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

/**
 * Returns a pointer to a link of a list corresponding to the index provided.
 * If the pointer is null, it returns NULL.
 * If the list is empty it returns NULL.
 * If the index is negative or zero, it returns the first item of the list.
 * If the index is greater or equal than the size of the list, it returns the last link of the list.
 */
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

/**
 * Appends a new link at the end of the list.
 * If the pointer is null, it returns NULL.
 * If it fails to allocate memory for the link or the string, it returns NULL.
 * If the list is empty it sets the first item as the new link.
 * Returns the pointer of the new link.
 */
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

/**
 * Appends a new link at the index position of the list.
 * If the pointer is null, it returns NULL
 * If it fails to allocate memory for the link or the string, it returns NULL.
 * If the list is empty it sets the first item as the new link.
 * If the index is negative or zero, it will add the new link at the begining of the list.
 * If the index is greater or equal than the size of the list. it adds the new link at the end of the list.
 * Returns the pointer of the new link.
 */
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

/**
 * Removes the last item of a string list.
 * If the pointer is null, it does nothing.
 * If the list is empty. it does nothing.
 */
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

/**
 * Removes the link at the index position of the list.
 * If the pointer is null, it does nothing.
 * If the list is empty. it does nothing.
 * If the index is negative or zero, it removes the first item of the list.
 * If the index is greater or equal than the size of the list. it removes the last item of a string list.
 */
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

/**
 * Destroys the list
 * If the pointer is null, it does nothing.
 */
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

#endif