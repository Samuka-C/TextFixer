#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG_LIB
#define DEBUG_LIB

#define DEBUG 1

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define logDebug(msg) \
    logDebugCaller(msg, __FILE__, __LINE__, __func__)

#define logWarning(msg) \
    logWarningCaller(msg, __FILE__, __LINE__, __func__)

#define logError(msg) \
    logErrorCaller(msg, __FILE__, __LINE__, __func__)

void logDebugCaller(const char* msg, const char* caller, int line, const char* func)
{
    if (DEBUG) printf("%sDEBUG (%s - %s() - line %d): %s%s\n", ANSI_COLOR_BLUE, caller, func, line, msg, ANSI_COLOR_RESET);
}

void logWarningCaller(const char* msg, const char* caller, int line, const char* func)
{
    if (DEBUG) printf("%sWARNING! (%s - %s() - line %d): %s%s\n", ANSI_COLOR_YELLOW, caller, func, line, msg, ANSI_COLOR_RESET);
}

void logErrorCaller(const char* msg, const char* caller, int line, const char* func)
{
    if (DEBUG) printf("%sERROR!! (%s - %s() - line %d): %s%s\n", ANSI_COLOR_RED, caller, func, line, msg, ANSI_COLOR_RESET);
}

#endif