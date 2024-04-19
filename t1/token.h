/*
    Tokens functions description
    Authors: Augusto dos Santos and Gabriel Nadalin
    Date: April 2024
*/
#ifndef TOKEN_H
#define TOKEN_H

#define MAX_LEXEMA_SIZE 200

// Tipos de Tokens
typedef enum {
    PalavraChave,
    StringLiteral,
    OpAritMult,
    OpAritDiv,
    OpAritSoma,
    OpAritSub,
    OpRelMenor,
    OpRelMenorIgual,
    OpRelMaiorIgual,
    BackArrow,
    OpRelMaior,
    OpRelIgual,
    OpRelDif,
    OpBoolE,
    OpBoolOu,
    DELIM,
    AbrePar,
    FechaPar,
    AbreCol,
    FechaCol,
    Virgula,
    Porcento,
    Circunflexo,
    EComercial,
    Ponto,
    PontoPonto,
    IDENT,
    NumInt,
    NumReal,
    Cadeia,
    Fim
} Token_type;

typedef struct {
    Token_type token_type;     // Guarda o tipo do token em uma string
    char * lexema;
    char * token_type_str;      // GAMBIARRA: Usado somente para palavras chave, por que elas sao tratadas diferente
}Token;

Token * create_token(Token_type token_type, char * lexema);
void clean_token(Token ** t);
char * get_token_Type(Token * t);
void print_token(Token * t);

#endif /* TOKEN_H */