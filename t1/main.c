#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "file_read.h"


// Reads any spaces or line break
int skip_spaces(){
    char c;
    do{
        c = read_buffer();
    }while(c == ' ' || c == '\n');

    regress_buffer();
}

Token * tokenOpRel(char c){
    char next_char;
    // Operadores relacionais

    if(c == '=')
        return create_token(OpRelIgual, "=");               // =

    if(c == '<'){
        next_char = read_buffer();
        if (next_char == '=')
            return create_token(OpRelMenorIgual, "<=");     // <= 
        if (next_char == '>')
            return create_token(OpRelDif, "<>");            // <>, different 
        regress_buffer();
        return create_token(OpRelMenor, "<");               // <
    }

    if(c == '>'){
        next_char = read_buffer();
        if (next_char == '=')
            return create_token(OpRelMaiorIgual, ">=");     // >=
        regress_buffer();   // Going back one pos
        return create_token(OpRelMaior, ">");               // >
    }
}

Token * tokenOpArit(char c){
    if(c == '*')
        return create_token(OpAritMult, "*");

    if(c == '/')
        return create_token(OpAritDiv, "/");

    if(c == '+')
        return create_token(OpAritSoma, "+");
        
    if(c == '-')
        return create_token(OpAritSub, "-");
}

// Recognizes a token 
Token * identify_token(){
    if(!tokens_available()){
        return NULL;
    }
    // Skipping spaces
    skip_spaces();
    
    // Reading char from buffer
    char c = read_buffer();

    // Operadores relacionais
    if(c == '=' || c == '>' || c == '<')
        return tokenOpRel(c);

    // Operadores aritméticos
    if(c == '*' || c == '/' || c == '+' || c == '-')
        return tokenOpArit(c);

    if(c == '\0'){
        printf("Reached EOF");
        return NULL;
    }
    // Else
    printf("Symbol \" %c \" not recognized\n", c);
    printf("%d\n", c);
    exit(1);
}

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