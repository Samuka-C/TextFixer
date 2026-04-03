#ifndef TEXT_FILE
#define TEXT_FILE

/// @brief Reads a string from a text file
/// @param path path to the text file
/// @return a pointer to a string. NULL if the was a error reading the file or allocating memory for the string
char *read_file(const char* path);

/// @brief Writes a string to a text file
/// @param path path to the text file
/// @param string string to write
/// @return 0 if could write with no problems, 1 if there was a problem
int write_file(const char* path, const char* string);

#endif
