#ifndef LANGAUGE_H
#define LANGAUGE_H
#include "token.h"

/* Tokens generation */
Token * identify_token();
Token * tokenOpRel(char c);
Token * tokenOpArit(char c);
Token * tokenNumber(char c);
Token * tokenString(char c);

/* Tools */
void skip_spaces();
void skip_comments();

int char_is_letter(char c);
int char_is_number(char c);

#endif /* LANGAUGE_H */