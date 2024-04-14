#ifndef TOKEN_H
#define TOKEN_H

#define MAX_LEXEMA_SIZE 200

// Tipos de Tokens
typedef enum {
    PCDeclaracoes,
    PCAlgoritmo,
    PCInteiro,
    PCReal,
    PCAtribuir,
    PCA,
    PCLer,
    PCImprimir,
    PCSe,
    PCEntao,
    PCSenao,
    PCEnquanto,
    PCInicio,
    PCFim,
    OpAritMult,
    OpAritDiv,
    OpAritSoma,
    OpAritSub,
    OpRelMenor,
    OpRelMenorIgual,
    OpRelMaiorIgual,
    OpRelMaior,
    OpRelIgual,
    OpRelDif,
    OpBoolE,
    OpBoolOu,
    Delim,
    AbrePar,
    FechaPar,
    Var,
    NumInt,
    NumReal,
    Cadeia,
    Fim
} Token_type;

typedef struct {
    Token_type token_type;     // Guarda o tipo do token em uma string
    char * lexema;
}Token;

Token * create_token(Token_type token_type, char * lexema);
char * get_token_Type(Token * t);
void print_token(Token * t);

#endif /* TOKEN_H */