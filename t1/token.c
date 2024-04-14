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
        case StringLiteral:     // GAMBIARRA: string literais estão sendo jogadas para o lexema, está certo isso?
            return "CADEIA";
        // Todas Palavras chave foram removidas, por hora
        // case PCDeclaracoes :
        //     return "Declare";
        // case PCAlgoritmo :
        //     return "PCAlgoritmo";
        // case PCInteiro:
        //     return "PCInteiro";
        // case PCReal :
        //     return "PCReal";
        // case PCAtribuir:
        //     return "PCAtribuir";
        // case PCA :
        //     return "PCA";
        // case PCLer :
        //     return "PCLer";
        // case PCImprimir :
        //     return "PCImprimir";
        // case PCSe :
        //     return "PCSe";
        // case PCEntao :
        //     return "PCEntao";
        // case PCSenao :
        //     return "PCSenao";
        // case PCEnquanto :
        //     return "PCEnquanto";
        // case PCInicio :
        //     return "PCInicio";
        // case PCFim :
        //     return "fim_algoritmo";
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
            return "\'%%\'";
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
            return "\'NUM_INT\'";
        case NumReal :
            return "\'NUM_REAL\'";
        case Cadeia :
            return "\'CADEIA\'";
        case Fim :
            return "\'Fim\'";
        default:
            perror("Error, there is not such token type");
            exit(1);
    }
}

// Returns a strin in the format < TokenType , "Lexema"\' >
void print_token(Token * t){
    if (t == NULL)
        printf("NULL token\n");
    else if (t->lexema == NULL)
        printf("< %s >", get_token_Type(t));
    else
        printf("<\'%s\',%s>", t->lexema, get_token_Type(t));
}

// Returns the token string
char * get_token_str(Token * t){
    char * token_str = calloc(sizeof(char), 50);    // Calloc so it starts everything with \0
    sprintf("<\'%s\',%s>",t->lexema, get_token_str(t));
    
    return token_str;
}