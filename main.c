/*
 * BinToC
 *
 * Reads in a binary file and creates a C file and matching header with its
 * contents.
 *
 *
 * Author:                      Jordan Conley
 * Date Created:                7th July 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

/* 
 * Creates an accompanying header file for the binary dump. Header file merely
 * contains an extern definition for the source file.
 */
static void make_header(FILE* outh, const char* variable) {
    if (!outh) {
        return;
    }

    fprintf(outh,
            "/* %s header */ \n"
            "#ifndef %s_H \n"
            "#define %s_H \n\n"
            "extern unsigned char %s[];\n\n"
            "#endif %s_H \n",
            variable, variable, variable, variable, variable);
}

/*
 * Creates the C source file for the binary dump.
 */
static void process(FILE* in, FILE* outc, const char* variable) {
    unsigned char buffer[BUFFER_SIZE];
    int bytes_read;
    int i;

    fprintf(outc, "const unsigned char %s[] = {", variable);

    do {
        bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, in);
        
        for (i = 0; i < bytes_read; i++) {
            if ((i%16) == 0) {
                fputs("\n    ", outc);
            }

            fprintf(outc, "0x%02X, ", (int) buffer[i]);

        }
    } while (bytes_read == BUFFER_SIZE);
    
    fprintf(outc, "};\n");
}

/*
 * main entry point
 */
int main(int argc, char** argv) {
    FILE* input = stdin;
    FILE* output_c = stdout;
    FILE* output_h = NULL;
    char* variable_name = "data";

    int i;
    char* key = NULL;
    char* value = NULL;
    char* long_name = NULL;

    for (i = 1; i < argc; i++) {
        key = strtok(argv[i], "="); 
        value = strtok(NULL, "");

        if (!strcmp("infile", key)) {
            input = fopen(value, "rb");
            if (!input) {
                fprintf(stderr, "Could not open file: %s\r\n", value);
                return 1;
            }
        } else if (!strcmp("outfile", key)) {
            long_name = calloc(sizeof(char), strlen(value) + 3);

            sprintf(long_name, "%s.c", value);
            output_c = fopen(long_name, "w");
            if (!output_c) {
                fprintf(stderr, "Could not open %s for writing\r\n", 
                        long_name);
                return 1;
            }

            sprintf(long_name, "%s.h", value);
            output_h = fopen(long_name, "w");
            if (!output_h) {
                fprintf(stderr, "Could not open %s for writing\r\n", 
                        long_name);
                return 1;
            }

            free(long_name);
        } else if (!strcmp("var", key)) {
            variable_name = value;
        } else {
            fprintf(stderr, "WARNING Unknown argument: %s\r\n", argv[i]);
        }
    }

    make_header(output_h, variable_name); 
    process(input, output_c, variable_name);

    if (input) fclose(input);
    if (output_c) fclose(output_c);
    if (output_h) fclose(output_h);

    return 0;
} 

