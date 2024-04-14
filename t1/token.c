#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

Token * create_token(Token_type token_type, char * lexema){
    Token * t = malloc(sizeof(Token));
    t->lexema = malloc(sizeof(char) * MAX_LEXEMA_SIZE);
    if (strlen(lexema) > MAX_LEXEMA_SIZE){
        perror("Lexema has a size bigger then the maximum allowed");
        exit(1);
    }
    strcpy(t->lexema, lexema);
    t->token_type = token_type;
    return t;
}

// Token * create_token(char * tipo_token, char * lexema){
//     Token * t = malloc(sizeof(Token));
//     t->lexema = malloc(sizeof(char) * MAX_LEXEMA_SIZE);
//     if (strlen(lexema) > MAX_LEXEMA_SIZE){
//         perror("Lexema has a size bigger then the maximum allowed");
//         exit(1);
//     }
//     strcpy(t->lexema, lexema);
//     t->token_type = token_type;
//     return t;
// }

char * get_token_Type(Token * t){
    switch (t->token_type){
        case PalavraChave:      // GAMBIARRA: Precisa arrumar, as palavras chaves deveriam ter um tipo para cada palavra, mas sao tratadas todas iguais aqui
            return t->token_type_str;
        case PCDeclaracoes :
            return "PCDeclaracoes";
        case PCAlgoritmo :
            return "PCAlgoritmo";
        case PCInteiro:
            return "PCInteiro";
        case PCReal :
            return "PCReal";
        case PCAtribuir:
            return "PCAtribuir";
        case PCA :
            return "PCA";
        case PCLer :
            return "PCLer";
        case PCImprimir :
            return "PCImprimir";
        case PCSe :
            return "PCSe";
        case PCEntao :
            return "PCEntao";
        case PCSenao :
            return "PCSenao";
        case PCEnquanto :
            return "PCEnquanto";
        case PCInicio :
            return "PCInicio";
        case PCFim :
            return "PCFim";
        case OpAritMult :
            return "OpAritMult";
        case OpAritDiv :
            return "OpAritDiv";
        case OpAritSoma :
            return "OpAritSoma";
        case OpAritSub :
            return "OpAritSub";
        case OpRelMenor :
            return "OpRelMenor";
        case OpRelMenorIgual :
            return "OpRelMenorIgual";
        case OpRelMaiorIgual :
            return "OpRelMaiorIgual";
        case OpRelMaior :
            return "OpRelMaior";
        case OpRelIgual :
            return "OpRelIgual";
        case OpRelDif :
            return "OpRelDif";
        case OpBoolE :
            return "OpBoolE";
        case OpBoolOu :
            return "OpBoolOu";
        case Delim :
            return "Delim";
        case AbrePar :
            return "AbrePar";
        case FechaPar :
            return "FechaPar";
        case IDENT :
            return "IDENT";
        case NumInt :
            return "NumInt";
        case NumReal :
            return "NumReal";
        case Cadeia :
            return "Cadeia";
        case Fim :
            return "Fim";
        default:
            perror("Error, there is not such token type");
            exit(1);
    }
}

// Returns a strin in the format < TokenType , "Lexema" >
void print_token(Token * t){
    if (t == NULL)
        printf("NULL token\n");
    else if (t->lexema == NULL)
        printf("< %s >", get_token_Type(t));
    else
        printf("< %s , \"%s\" >", get_token_Type(t), t->lexema);
}