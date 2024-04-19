/*
    Tokens functions implementations
    Authors: Augusto dos Santos and Gabriel Nadalin
    Date: April 2024
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

// Creates a token based on a tokne_type and it's "lexema"
Token * create_token(Token_type token_type, char * lexema){
    Token * t = malloc(sizeof(Token));
    t->lexema = malloc(sizeof(char) * MAX_LEXEMA_SIZE);
    if (strlen(lexema) > MAX_LEXEMA_SIZE){
        perror("Lexema has a size bigger then the maximum allowed");
        exit(1);
    }
    strcpy(t->lexema, lexema);
    t->token_type = token_type;
    t->token_type_str = NULL;
    return t;
}

// Dealocates token
void clean_token(Token ** t){
    if(*t == NULL) return;
    free((*t)->lexema);
    if ((*t)->token_type_str != NULL)       // Sometimes this field is not used
        free((*t)->token_type_str);
    free(*t);
    *t = NULL;
}

// Returns the token type as a string
char * get_token_Type(Token * t){
    switch (t->token_type){
        case PalavraChave:      // Por motivos de simplicidade, todas palavras chaves foram tratadas como iguais
            return t->token_type_str;
        case StringLiteral:
            return "CADEIA";
        case OpAritMult :
            return "\'*\'";
        case OpAritDiv :
            return "\'/\'";
        case OpAritSoma :
            return "\'+\'";
        case OpAritSub :
            return "\'-\'";
        case OpRelMenor :
            return "\'<\'";
        case OpRelMenorIgual :
            return "\'<=\'";
        case BackArrow :
            return "\'<-\'";
        case OpRelMaiorIgual :
            return "\'>=\'";
        case OpRelMaior :
            return "\'>\'";
        case OpRelIgual :
            return "\'=\'";
        case OpRelDif :
            return "\'<>\'";
        case OpBoolE :
            return "\'OpBoolE\'";
        case OpBoolOu :
            return "\'OpBoolOu\'";
        case DELIM :
            return "\':\'";
        case AbrePar :
            return "\'(\'";
        case FechaPar :
            return "\')\'";
        case AbreCol :
            return "\'[\'";
        case FechaCol :
            return "\']\'";
        case Virgula :
            return "\',\'";
        case Porcento :
            return "\'%\'";
        case Circunflexo :
            return "\'^\'";
        case EComercial:
            return "\'&\'";
        case Ponto :
            return "\'.\'";
        case PontoPonto :
            return "\'..\'";
        case IDENT :
            return "IDENT";
        case NumInt :
            return "NUM_INT";
        case NumReal :
            return "NUM_REAL";
        case Cadeia :
            return "CADEIA";
        case Fim :
            return "\'Fim\'";
        default:
            perror("Error, there is not such token type");
            exit(1);
    }
}

// Prints the token in console formated as < TokenType , "Lexema"\' >
void print_token(Token * t){
    if (t == NULL)
        printf("NULL token\n");
    else if (t->lexema == NULL)
        printf("< %s >", get_token_Type(t));
    else
        printf("<\'%s\',%s>", t->lexema, get_token_Type(t));
}