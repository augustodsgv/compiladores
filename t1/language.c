#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "file_read.h"
#include "language.h"

char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

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

    // Integer or float number
    if (char_is_number(c))
        return tokenNumber(c);

    if(c == '\0'){
        printf("Reached EOF");
        return NULL;
    }
    // Else
    printf("Symbol \" %c \" not recognized\n", c);
    printf("%d\n", c);
    exit(1);
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

Token * tokenNumber(char c){
    char next_char;
    char * number_str;          // Stores the number string
    char integer_buffer[20] = {0};    // Integer number with maximum of 20 digits. Allocated with {0} to prevent garbage to output
    char float_buffer[20] = {0};      // Float part with maximum of 20 digits
    int integer_buffer_pos = 0;
    int float_buffer_pos = 0;
    char int_or_float = 'i';    // Flag checks if number is integer or float. Default for integer

    // Adding first char to int buffer
    integer_buffer[integer_buffer_pos++] = c;

    // Treating integer part
    while(1){
        if(!tokens_available()) break;            // EOF, cannot read more
        next_char = read_buffer();
        if (!char_is_number(next_char)){  // End of number or end of integer part 
            if(next_char == '.')            // It is a float number
                int_or_float = 'f';
            else
                regress_buffer();       // Returning not number to the buffer
            break;
        }
        integer_buffer[integer_buffer_pos++] = next_char;
    }

    if (int_or_float == 'f'){
        // Checking if after the '.' there is another number, otherwise it's not a valid float number
        next_char = read_buffer();
        if(!char_is_number(next_char));
            // TODO: throw error
        
        // Reading the float part
        float_buffer[float_buffer_pos++] = next_char;
        while(1){
            if(!tokens_available()) break;            // EOF, cannot read more

            next_char = read_buffer();
            if (!char_is_number(next_char)){  // End of float part
                regress_buffer();
                break;
            }
            float_buffer[float_buffer_pos++] = next_char;
        }
        number_str = malloc(sizeof(char) * 41);
        sprintf(number_str, "%s.%s", integer_buffer, float_buffer);
        return create_token(NumReal, number_str);
    }
    number_str = malloc(sizeof(char) * 21);
    strcpy(number_str, integer_buffer);
    return create_token(NumInt, number_str);
}

/* Tools */
// Reads any spaces or line break
int skip_spaces(){
    char c;
    do{
        c = read_buffer();
    }while(c == ' ' || c == '\n');

    regress_buffer();
}

// Checks if a char is an alphabet letter
int char_is_letter(char c){
    for(int i = 0; i < 26; i++)
        if (c == letters[i]) return 1;
    return 0;
}

// Checks if a char is a number
int char_is_number(char c){
    for(int i = 0; i < 10; i++)
        if (c == numbers[i]) return 1;
    return 0;
}