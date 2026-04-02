#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "debug/debug.h"
#include "string basic/string_basic.h"
#include "string process/string_op.h"
#include "string list/string_list.h"

enum alignType
{
    LEFT,
    RIGHT,
    CENTER,
    JUSTIFY
};

/// @brief Prints the help text explaining how to use the program
void print_help()
{
    printf("Usage: .\\textFixer [options] <input> <line length>\n");
    printf("\nOptions:\n");
    printf("  -h, --help           Show this help message\n");
    printf("  -f, --file           Treat input as file path\n");
    printf("  -l, --left           Align the lines to the left\n");
    printf("  -r, --right          Align the lines to the right\n");
    printf("  -c, --center         Align the lines to the center\n");
    printf("  -j, --just           Justify the lines (default if no option is given)\n");
    printf("  -o, --output <file>  Output file\n");
}

/// @brief Reads a string from a text file
/// @param path path to the text file
/// @return a pointer to a string. NULL if the was a error reading the file or allocating memory for the string
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

/// @brief Writes a string to a text file
/// @param path path to the text file
/// @param string string to write
/// @return 0 if could write with no problems, 1 if there was a problem
int write_file(const char* path, const char* string)
{
    FILE *file = fopen(path, "w");

    if (file == NULL)
    {
        logError("could not create or open file in (%s)", path);
        return 1;
    }

    fprintf(file, string);

    fclose(file);
    return 0;
}

int main(int argc, char *argv[])
{
    int opt;
    int option_index = 0;

    int treat_as_file = 0;
    char *output_file_path = NULL;

    enum alignType type = JUSTIFY;

    struct option long_options[] = 
    {
        {"help", no_argument, NULL, 'h'},
        {"file", no_argument, NULL, 'f'},
        {"left", no_argument, NULL, 'l'},
        {"right", no_argument, NULL, 'r'},
        {"center", no_argument, NULL, 'c'},
        {"just", no_argument, NULL, 'j'},
        {"output", required_argument, NULL, 'o'},
        {NULL, 0, NULL, 0}
    };

    while ((opt = getopt_long(argc, argv, "hflrcjo:", long_options, &option_index)) != -1)
    {
        switch (opt)
        {
            case 'h':
                print_help();
                return 0;
            case 'f':
                treat_as_file = 1;
                break;
            case 'l':
                type = LEFT;
                break;
            case 'r':
                type = RIGHT;
                break;
            case 'c':
                type = CENTER;
                break;
            case 'j':
                type = JUSTIFY;
                break;
            case 'o':
                output_file_path = optarg;
                break;
            default:
                print_help();
                return 1;
        }
    }

    // Remaining arguments = input and line length
    if (optind >= argc)
    {
        logError("missing input");
        print_help();
        return 1;
    }

    if (optind + 1 >= argc)
    {
        logError("missing line lenght");
        print_help();
        return 1;
    }

    char *input = argv[optind];
    int line_length = atoi(argv[optind + 1]); 

    char *data = NULL;

    if (treat_as_file)
    {
        data = read_file(input);
        if (data == NULL)
            return 1;
    }
    else
        data = input;

    char *output;

    switch (type)
    {
        case LEFT:
            output = alignLeft(data, line_length);
            break;
        case RIGHT:
            output = alignRight(data, line_length);
            break;
        case CENTER:
            output = alignCenter(data, line_length);
            break;
        case JUSTIFY:
            output = alignJustify(data, line_length);
            break;
    }

    if (output == NULL)
    {
        printf("unable to separate the string in lines of size %d\n", line_length);
        return 1;
    }

    if (output_file_path != NULL)
    {
        if (write_file(output_file_path, output))
        {
            printf("unable to write output to output file!\n");
            return 1;
        }
        
        printf("output written to output file with sucess!\n");
        return 0;
    }
    
    printf("output:\n%s\n", output);
    return 0;

}
