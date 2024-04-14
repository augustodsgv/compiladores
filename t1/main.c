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
        fprintf(stderr, "Missing file name parameter\n");
        exit(1);
    }
    
    if (!open_file(argv[1])){
        perror("Failed to open source code file");
        exit(1);
    }

    start_buffer();

    while(tokens_available()){
        Token * t = identify_token();
        print_token(t);
        printf("\n");
    }

    return 0;
}