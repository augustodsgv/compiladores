#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "file_read.h"
#include "language.h"

char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
// char special_char_identifiers[] = {'_'}; // Chars for building identifiers that are not letters neither numbers
char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char * keywords[] = {"algoritmo",  "declare",  "literal",  "inteiro",  "leia",  "escreva",  "fim_algoritmo",  "real",  "literal" 
,  "logico",  "fim_se",  "senao",  "entao",  "se",  "ou",  "fim_caso",  "para",  "ate",  "faca",  "fim_para"
,  "fim_enquanto",  "fim_para",  "seja",  "caso",  "enquanto",  "registro",  "fim_registro"
,  "tipo",  "fim_procedimento",  "procedimento",  "var",  "funcao",  "fim_funcao"
,  "retorne",  "constante",  "falso",  "verdadeiro"};

// Recognizes a token 
Token * identify_token(){
    if(!tokens_available()){
        return NULL;
    }
    // Skipping spaces
    skip_spaces();
    
    // Reading char from buffer
    char c = read_buffer();

    // TODO: this does not treats comments after comments
    // Skipping comments, if there are any
    if(c == '{'){
        skip_comments();
        skip_spaces();
        c = read_buffer();      // Reading next non comment char
    }

    // Operadores relacionais
    if(c == '=' || c == '>' || c == '<')
        return token_op_rel(c);

    // Operadores aritméticos
    if(c == '*' || c == '/' || c == '+' || c == '-')
        return token_op_arit(c);

    if (c == '.' || c == ':' || c == '(' || c == ')' || c == '[' || c == ']' || c == ',' || c == '%' || c == '^' || c == '&')
        return token_special_char(c);

    if (c == '\"')
        return token_literal_string('\"');

    // Integer or float number
    if (char_is_number(c))
        return token_number(c);

    if (char_is_letter(c))
        return token_string(c);

    if(c == '\0'){
        printf("Reached EOF");
        return NULL;
    }
    // Else
    printf("Symbol \" %c \" not recognized\n", c);
    printf("%d\n", c);
    exit(1);
}

Token * token_op_rel(char c){
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

Token * token_op_arit(char c){
    if(c == '*')
        return create_token(OpAritMult, "*");

    if(c == '/')
        return create_token(OpAritDiv, "/");

    if(c == '+')
        return create_token(OpAritSoma, "+");
        
    if(c == '-')
        return create_token(OpAritSub, "-");
}

Token * token_number(char c){
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
    // Checking if after the '.' there is another number, otherwise it's not a valid float number
    next_char = read_buffer();
    if(!char_is_number(next_char)){
        regress_buffer();
        int_or_float == 'i';
    }
    if (int_or_float == 'f'){
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

Token * token_string(char c){
    char token_string[50];       // Supposing string can have, at maximum, 50 characters long
    int token_string_pos = 0;
    char next_char;
    token_string[token_string_pos++] = c;

    while(1){
        if(!tokens_available()) break;  // Breaks if reaches end of tokens
        next_char = read_buffer();
        
        if(!is_valid_identifier(next_char)){    // Ended building identifier string
            regress_buffer();
            break;
        }
        token_string[token_string_pos++] = next_char;
    }

    token_string[token_string_pos] = '\0';
    // Checking for key words
    for(int i = 0; i < 37; i++){
        if(!strcmp(token_string, keywords[i])){    // Case it's a keyword
            // GAMBIARRA: criei um atributo novo de type_str para guardar o texto a ser guardado nos tokens de keyword.
            // Precisamos criar um método para guardar o tipo da keyword tb, mas não sei bem todos os que tem
            Token * t = create_token(PalavraChave, token_string);
            t->token_type_str = malloc(sizeof(char) * 50);
            sprintf(t->token_type_str, "\'%s\'", token_string);
            // strcpy(t->token_type_str, token_string);
            return t;
        }
    }

    // Otherwise, it will be consider an identifier
    return create_token(IDENT, token_string);

}

Token * token_special_char(char c){
    if(c == '(')
        return create_token(AbrePar, "(");
    if(c == ')')
        return create_token(FechaPar, ")");
    if(c == '[')
        return create_token(AbreCol, "[");
    if(c == ']')
        return create_token(FechaCol, "]");
    if(c == ',')
        return create_token(Virgula, ",");
    if(c == '%')
        return create_token(Porcento, "%%");
    if(c == ':')
        return create_token(DELIM, ":");
    if(c == '^')
        return create_token(Circunflexo, "^");
    if(c == '&')
        return create_token(EComercial, "&");
    
    if(c == '.'){
        if(read_buffer() == '.')
            return create_token(PontoPonto, "..");
        regress_buffer();
        return create_token(Ponto, ".");
    }
    
}

Token * token_literal_string(char c){
    char literal_string[200] = {0};     // Stores literal strings up to 200 characters
    int literal_string_pos = 0;
    char next_char;
    int closed_quotes = 0;
    
    literal_string[literal_string_pos++] = c;
    
    while(1){
        if(reached_EOF()) break;
        
        next_char = read_buffer();
        if(next_char == '\n')   // Broke a line without closing quotes
            break;
        
        literal_string[literal_string_pos++] = next_char;

        if(next_char == '\"'){      // Verification is after because it's needed to print '"' as well
        
            closed_quotes = 1;
            break;
        }
        
    }

    if(!closed_quotes){
        printf("Sintax error: Unclosed quotes at \"%s\"", literal_string);
        exit(1);
    }
    return create_token(StringLiteral, literal_string);
}
/* Tools */
// Reads any spaces or line break
void skip_spaces(){
    char c;
    do{
        c = read_buffer();
    }while(c == ' ' || c == '\n' || c == '\r' || c == '\t');

    regress_buffer();
}


// Skips comments
// Coments starts with '{' and ends with '}' or a \n
void skip_comments(){
    char next_char;
    int closed_comment = 0;

    while(1){
        if(!tokens_available()) break;  // End of tokens to read
        next_char = read_buffer();

        if (next_char == '}'){          // Closed comment
            closed_comment = 1;
            break;
        }
        if (next_char == '\n')          // Invalid comment, throw error
            break;
    }

    if (!closed_comment){               // Unclosed comments are found by \n or by EOF without closing
        printf("Sintaxe error: unclosed comment\n");
        exit(1);
    }
}


// Checks if a char is an alphabet letter
int char_is_letter(char c){
    for(int i = 0; i < 52; i++)
        if (c == letters[i]) return 1;
    return 0;
}

// Checks if a char is a number
int char_is_number(char c){
    for(int i = 0; i < 10; i++)
        if (c == numbers[i]) return 1;
    return 0;
}
// Checks if char is a valid for building identifiers
// Only checks for second or later characters in the identifier
int is_valid_identifier(char c){
    if(char_is_letter(c)) return 1;
    if(char_is_number(c)) return 1;
    if (c == '_') return 1;

    return 0;
}