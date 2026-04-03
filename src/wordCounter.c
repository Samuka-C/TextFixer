#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "debug/debug.h"
#include "string basic/string_basic.h"
#include "string basic/text_file.h"
#include "string list/string_list.h"
#include "string process/string_op.h"

/// @brief Prints the help text explaining how to use the program
void print_help()
{
    printf("Usage: .\\wordCounter [options] <input>\n");
    printf("\nOptions:\n");
    printf("  -h, --help           Show this help message\n");
    printf("  -f, --file           Treat input as file path\n");
    printf("  -o, --output <file>  Output file\n");
}

int main(int argc, char *argv[])
{
    int opt;
    int option_index = 0;

    int treat_as_file = 0;
    char *output_file_path = NULL;

    struct option long_options[] = 
    {
        {"help", no_argument, NULL, 'h'},
        {"file", no_argument, NULL, 'f'},
        {"output", required_argument, NULL, 'o'},
        {NULL, 0, NULL, 0}
    };

    while ((opt = getopt_long(argc, argv, "hfo:", long_options, &option_index)) != -1)
    {
        switch (opt)
        {
            case 'h':
                print_help();
                return 0;
            case 'f':
                treat_as_file = 1;
                break;
            case 'o':
                output_file_path = optarg;
                break;
            default:
                print_help();
                return 1;
        }
    }

    // Remaining arguments = input
    if (optind >= argc)
    {
        logError("missing input");
        print_help();
        return 1;
    }

    char *input = argv[optind];
    char *data = NULL;

    if (treat_as_file)
    {
        data = read_file(input);
        if (data == NULL)
            return 1;
    }
    else
        data = input;

    char *output = graphWordCount(countWords(separateStringIntoWords(filterOnlyLetters(data))));

    logDebug("graph:\n%s", output);

    if (output == NULL)
    {
        printf("unable to make the graph");
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