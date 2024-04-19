/*
    Description: Language logic declaration for token recognition
    Authors: Augusto dos Santos and Gabriel Nadalin
    Date: April 2024
*/
#ifndef LANGUAGE_H
#define LANGUAGE_H
#include "token.h"

/* Tokens generation */
Token * identify_token();
Token * token_op_rel(char c);
Token * token_op_arit(char c);
Token * token_number(char c);
Token * token_string(char c);
Token * token_special_char(char c);
Token * token_literal_string(char c, FILE * out_file);

/* Tools */
void skip_spaces();
void skip_comments();

int is_valid_identifier(char c);
int char_is_letter(char c);
int char_is_number(char c);
int get_line();

#endif /* LANGuAGE_H */