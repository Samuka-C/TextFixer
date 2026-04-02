#ifndef DEBUG_LIB
#define DEBUG_LIB

#define DEBUG 0

#if DEBUG
    #define logDebug(fmt, ...) \
        logDebugCaller(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#else
    #define logDebug(fmt, ...) ((void)0)
#endif

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