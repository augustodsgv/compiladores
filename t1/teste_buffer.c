#include <stdio.h>
#include <stdlib.h>
#include "file_read.h"

int main(int argc, char * argv[]){
    int n_iterations = 20;
    if(argc > 1){
        n_iterations = strtol(argv[1], NULL, 10);
    }
    open_input_file("arquivo.txt");
    start_buffer();
    print_buffer();
    for(int i = 0; i < n_iterations; i++){
        read_buffer();
        print_buffer();
    }
    
    return 0;
}