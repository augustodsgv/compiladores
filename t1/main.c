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

    start_buffer();

    while(tokens_available()){
        Token * t = identify_token();
        fprintf(out_file, "<\'%s\',%s>\n",t->lexema, get_token_Type(t));
        // print_token(t);
        // printf("\n");
    }

    return 0;
}