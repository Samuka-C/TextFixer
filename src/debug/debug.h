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

#define logDebug(fmt, ...) \
    logDebugCaller(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#define logWarning(fmt, ...) \
    logWarningCaller(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#define logError(fmt, ...) \
    logErrorCaller(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

/**
 * Shows a debug message on the console only if DEBUG is true
 */
void logDebugCaller(const char* file, int line, const char* func, const char* fmt, ...);

/**
 * Shows a warning message on the console
 */
void logWarningCaller(const char* file, int line, const char* func, const char* fmt, ...);

/**
 * Shows a error message on the console
 */
void logErrorCaller(const char* file, int line, const char* func, const char* fmt, ...);

#endif