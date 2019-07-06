#ifndef _LEX_ANALYSER_H_
#define _LEX_ANALYSER_H_

#include <stdlib.h>

typedef unsigned int uint;

// LP - left parentheses
// RP - right parentheses
// EOI - end of input
enum TOKENS { EOI, NUM, PLUS, STAR, LP, RP, UNKNOWN };

typedef struct token_lexeme
{
	enum TOKENS token;
	char lexeme;
} token_lexeme;

void set_input_stream(char* input);
token_lexeme get_next_token(void);
void set_token_index(uint index);
uint get_token_index(void);

#endif 
