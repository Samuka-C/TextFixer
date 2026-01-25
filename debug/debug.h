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

/**
 * Shows a debug message on the console only if DEBUG is true
 */
void logDebugCaller(const char* msg, const char* caller, int line, const char* func);

/**
 * Shows a warning message on the console
 */
void logWarningCaller(const char* msg, const char* caller, int line, const char* func);

/**
 * Shows a error message on the console
 */
void logErrorCaller(const char* msg, const char* caller, int line, const char* func);

#endif