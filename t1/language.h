#ifndef LANGAUGE_H
#define LANGAUGE_H
#include "token.h"

Token * identify_token();
int skip_spaces();
Token * tokenOpRel(char c);
Token * tokenOpArit(char c);
Token * tokenNumber(char c);

int char_is_letter(char c);
int char_is_number(char c);

#endif /* LANGAUGE_H */