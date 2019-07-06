#ifndef  _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <stdlib.h>

#include "../LexAnalyzer/lex_analyzer.h"

void parse_input(char* input_str);
static int stmt(token_lexeme token);
static int expr(token_lexeme token);
static int term(token_lexeme token);
static int fact(token_lexeme token);

#endif 
