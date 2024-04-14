#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "file_read.h"
#include "language.h"


int main(int argc, char * argv[]){
    if (argc < 2){
        fprintf(stderr, "Missing file name parameter\n");
        // printf("Missing file name parameter\n");
        exit(1);
    }

    // char * file_name = argv[1];
    // char * file_name = "arquivo.txt";
    
    if (!open_file(argv[1])){
        perror("Failed to open file");
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