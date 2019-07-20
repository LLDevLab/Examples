#include "lex_analyzer.h"

static uint input_index;
static char* input_str = NULL;

void set_input_stream(char* input)
{
	input_str = input;
	input_index = 0;
}

void set_token_index(uint index)
{
	input_index = index;
}

uint get_token_index(void)
{
	return input_index;
}

token_lexeme get_next_token(void)
{
	token_lexeme token = 
	{
					.token = EOI
	};

	switch (input_str[input_index])
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		token.token = NUM;
		break;
	case '+':
		token.token = PLUS;
		break;
	case '*':
		token.token = STAR;
		break;
	case '(':
		token.token = LP;
		break;
	case ')':
		token.token = RP;
		break;
	default:
		if(strlen(input_str) > input_index)
			token.token = UNKNOWN;
		break;
	}

	if (token.token != EOI)
	{
		token.lexeme = input_str[input_index];
		input_index++;
	}

	return token;
}