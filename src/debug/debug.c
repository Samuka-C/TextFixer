#include "debug.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

char* format(const char* fmt, va_list args)
{
    va_list args_copy;
    va_copy(args_copy, args);

    int len = vsnprintf(NULL, 0, fmt, args_copy);
    va_end(args_copy);

    char* buffer = malloc(len+1);
    vsnprintf(buffer, len + 1, fmt, args);
    va_end(args);

    return buffer;
}

void logDebugCaller(const char* file, int line, const char* func, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char* msg = format(fmt, args);

    if (DEBUG) printf("%sDEBUG (%s - %s() - line %d): %s%s\n", ANSI_COLOR_BLUE, file, func, line, msg, ANSI_COLOR_RESET);

    free(msg);
}

void logWarningCaller(const char* file, int line, const char* func, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char* msg = format(fmt, args);

    printf("%sWARNING! (%s - %s() - line %d): %s%s\n", ANSI_COLOR_YELLOW, file, func, line, msg, ANSI_COLOR_RESET);

    free(msg);
}

void logErrorCaller(const char* file, int line, const char* func, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char* msg = format(fmt, args);

    printf("%sERROR!! (%s - %s() - line %d): %s%s\n", ANSI_COLOR_RED, file, func, line, msg, ANSI_COLOR_RESET);

    free(msg);
}
