#ifndef LANGAUGE_H
#define LANGAUGE_H
#include "token.h"

/* Tokens generation */
Token * identify_token();
Token * token_op_rel(char c);
Token * token_op_arit(char c);
Token * token_number(char c);
Token * token_string(char c);
Token * token_special_char(char c);
Token * token_literal_string(char c);

/* Tools */
void skip_spaces();
void skip_comments();

int is_valid_identifier(char c);
int char_is_letter(char c);
int char_is_number(char c);

#endif /* LANGAUGE_H */