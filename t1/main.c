/*
    Description: Main function of the lexic analyser built for the "Compilers" subject
    Authors: Augusto dos Santos and Gabriel Nadalin
    Date: April 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "file_read.h"
#include "language.h"

int main(int argc, char * argv[]){
    // 0 file name
    // 1 input file (source code)
    // 2 output file
    if (argc < 2){
        fprintf(stderr, "Missing source file name parameter\n");
        exit(1);
    }
    if (argc < 3){
        fprintf(stderr, "Missing output file name parameter\n");
        exit(1);
    }
    if (!open_input_file(argv[1])){
        perror("Failed to open source code file (input file)");
        exit(1);
    }
    
    FILE * out_file = fopen(argv[2], "w");

    if (out_file == NULL){
        perror("Failed to open token file (output file)");
        exit(1);
    }

    start_buffer();         // Alocating buffer and making first load

    // Loops while don't reach EOF
    while(!reached_EOF()){
        Token * t = identify_token(out_file);
        if (t != NULL){     // Testando se é um token válido
            fprintf(out_file, "<\'%s\',%s>\n",t->lexema, get_token_Type(t));
            clean_token(&t);
        }
    }

    // Closing files
    close_input_file();
    fclose(out_file);

    return 0;
}