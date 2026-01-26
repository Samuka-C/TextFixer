#ifndef STRING_LIST
#define STRING_LIST

typedef struct string_list_link_struct string_list_link;

typedef struct string_list_struct string_list;

/**
 * Creates a new empty string list.
 * If it fails to allocate memory for the list, it returns NULL.
 * Returns a pointer to the new list.
 */
string_list* strLst_Create();

/**
 * Returns 1 if the list is empty. otherwise it returns 0.
 * If the pointer is null it returns -1 (which still counts as true).
 */
int strLst_CheckEmpty(string_list* stringList);

/**
 * Returns the size of a list.
 * If the pointer is null, it returns -1.
 */
int strLst_GetSize(string_list* stringList);

/**
 * Returns a pointer to the last link of a list.
 * If the pointer is null, it returns NULL.
 * If the list is empty it returns NULL.
 */
string_list_link* strLst_GetLastLink(string_list* stringList);

/**
 * Returns a pointer to a link of a list corresponding to the index provided.
 * If the pointer is null, it returns NULL.
 * If the list is empty it returns NULL.
 * If the index is negative or zero, it returns the first item of the list.
 * If the index is greater or equal than the size of the list, it returns the last link of the list.
 */
string_list_link* strLst_GetLink(string_list* stringList, int index);

/**
 * Prints all the strings in the list
 */
void strLst_Print(string_list* stringList);

/**
 * Appends a new link at the end of the list.
 * If the pointer is null, it returns NULL.
 * If it fails to allocate memory for the link or the string, it returns NULL.
 * If the list is empty it sets the first item as the new link.
 * Returns the pointer of the new link.
 */
string_list_link* strLst_Append(string_list* stringList, const char* string);

/**
 * Appends a new link at the index position of the list.
 * If the pointer is null, it returns NULL
 * If it fails to allocate memory for the link or the string, it returns NULL.
 * If the list is empty it sets the first item as the new link.
 * If the index is negative or zero, it will add the new link at the begining of the list.
 * If the index is greater or equal than the size of the list. it adds the new link at the end of the list.
 * Returns the pointer of the new link.
 */
string_list_link* strLst_AppendAt(string_list* stringList, const char* string, int index);

/**
 * Removes the last item of a string list.
 * If the pointer is null, it does nothing.
 * If the list is empty. it does nothing.
 */
void strLst_Remove(string_list* stringList);

/**
 * Removes the link at the index position of the list.
 * If the pointer is null, it does nothing.
 * If the list is empty. it does nothing.
 * If the index is negative or zero, it removes the first item of the list.
 * If the index is greater or equal than the size of the list. it removes the last item of a string list.
 */
void strLst_RemoveAt(string_list* stringList, int index);

/**
 * Destroys the list
 * If the pointer is null, it does nothing.
 */
void strLst_Destroy(string_list* stringList);

#endif