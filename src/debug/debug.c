#include "debug.h"

#include <stdio.h>
#include <stdlib.h>

void logDebugCaller(const char* msg, const char* caller, int line, const char* func)
{
    if (DEBUG) printf("%sDEBUG (%s - %s() - line %d): %s%s\n", ANSI_COLOR_BLUE, caller, func, line, msg, ANSI_COLOR_RESET);
}

void logWarningCaller(const char* msg, const char* caller, int line, const char* func)
{
    printf("%sWARNING! (%s - %s() - line %d): %s%s\n", ANSI_COLOR_YELLOW, caller, func, line, msg, ANSI_COLOR_RESET);
}

void logErrorCaller(const char* msg, const char* caller, int line, const char* func)
{
    printf("%sERROR!! (%s - %s() - line %d): %s%s\n", ANSI_COLOR_RED, caller, func, line, msg, ANSI_COLOR_RESET);
}
