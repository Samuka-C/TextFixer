#include <stdio.h>
#include <stdlib.h>

#include "../debug/debug.h"

char *read_file(const char* path)
{
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        logError("file in path (%s) could not be read!", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    logDebug("size: %d", size);

    char *buffer = (char*)malloc((size + 1) * sizeof(char));
    if (buffer == NULL)
    {
        logError("could not allocate memory to store text from file in (%s)!", path);
        fclose(file);
        return NULL;
    }

    logDebug("buffer address: %p", (void*)buffer);

    int count = fread(buffer, 1, size, file);
    logDebug("count: %d", count);

    buffer[size] = '\0';
    logDebug("text in the buffer: %s", buffer);

    fclose(file);
    return buffer;
}

int write_file(const char* path, const char* string)
{
    FILE *file = fopen(path, "w");

    if (file == NULL)
    {
        logError("could not create or open file in (%s)", path);
        return 1;
    }

    fprintf(file, "%s", string);

    fclose(file);
    return 0;
}