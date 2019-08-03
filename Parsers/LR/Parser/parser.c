#include "parser.h"

static int parse_stack[PARSE_STACK_SIZE];
static int value_stack[VALUE_STACK_SIZE];
static int reduction_table[REDUCTION_TABLE_ROWS][REDUCTION_TABLE_COLS];
static int parse_stack_pos = -1;
static int value_stack_pos = -1;

static enum NONTERMINALS { 
							STMT = 10, 
							EXPR = 11,  
							TERM = 12, 
							FACT = 13
						};

int parse_input(char* input_str)
{
	token_lexeme token;

	init();

	set_input_stream(input_str);

	token = get_next_token();

	if (token.token != UNKNOWN)
		shift(&token);

	while (parse_stack[parse_stack_pos] != STMT)
	{
		switch (parse_stack[parse_stack_pos])
		{
		case EXPR:
			if (token.token == PLUS || token.token == RP)
				shift(&token);
			else
				reduce(0);
			break;
		case TERM:
			if (token.token == STAR)
				shift(&token);
			else
			{
				if (parse_stack_pos > 0 && parse_stack[parse_stack_pos - 1] == PLUS)
					reduce(3);
				else
					reduce(2);
			}
				
			break;
		case FACT:
			if (parse_stack_pos > 0 && parse_stack[parse_stack_pos - 1] == STAR)
				reduce(5);
			else
				reduce(4);
			break;
		case LP:
		case PLUS:
		case STAR:
			shift(&token);
			break;
		case NUM:
			reduce(6);
			break;
		case RP:
			reduce(7);
			break;
		default:
			break;
		}
	}

	return pop_value_stack();
}

static void shift(token_lexeme* token)
{
	parse_stack_pos++;
	parse_stack[parse_stack_pos] = token->token;

	if(token->token == NUM)
		push_value_stack(atoi(&token->lexeme));

	*token = get_next_token();
}

static void reduce(int table_index)
{
	int i;
	int lhs;
	int tmp_val = 0;

	for (i = REDUCTION_TABLE_COLS - 1; i >= 0 ; i--)
	{
		if (reduction_table[table_index][i] == EMPTY)
			continue;

		if (parse_stack[parse_stack_pos] == reduction_table[table_index][i])
		{
			parse_stack[parse_stack_pos] = EMPTY;
			parse_stack_pos--;
		}
	}

	switch (table_index)
	{
	case 0:
	case 1:
		lhs = STMT;			
		break;
	case 2:
		lhs = EXPR;
		break;
	case 3:
		lhs = EXPR;

		tmp_val = pop_value_stack();
		tmp_val += pop_value_stack();

		push_value_stack(tmp_val);

		break;
	case 4:
		lhs = TERM;
		break;
	case 5:
		lhs = TERM;

		tmp_val = pop_value_stack();
		tmp_val *= pop_value_stack();

		push_value_stack(tmp_val);

		break;
	case 6:
	case 7:
		lhs = FACT;
		break;
	default:
		lhs = 0;
		break;
	}

	parse_stack_pos++;
	parse_stack[parse_stack_pos] = lhs;
}

static void init_reduction_table(void)
{
	int i;

	for (i = 0; i < REDUCTION_TABLE_ROWS; i++)
	{
		switch (i)
		{
		case 0:										// stmt -> expr
			reduction_table[i][0] = EXPR;
			reduction_table[i][1] = EMPTY;
			reduction_table[i][2] = EMPTY;
			break;
		case 1:										// stmt -> Epsilon
			reduction_table[i][0] = EMPTY;
			reduction_table[i][1] = EMPTY;
			reduction_table[i][2] = EMPTY;
			break;
		case 2:										// expr -> term
			reduction_table[i][0] = TERM;
			reduction_table[i][1] = EMPTY;
			reduction_table[i][2] = EMPTY;
			break;
		case 3:										// expr -> expr + term
			reduction_table[i][0] = EXPR;
			reduction_table[i][1] = PLUS;
			reduction_table[i][2] = TERM;
			break;
		case 4:										// term -> fact
			reduction_table[i][0] = FACT;
			reduction_table[i][1] = EMPTY;
			reduction_table[i][2] = EMPTY;
			break;
		case 5:										// term -> term * fact
			reduction_table[i][0] = TERM;
			reduction_table[i][1] = STAR;
			reduction_table[i][2] = FACT;
			break;
		case 6:										// fact -> NUM
			reduction_table[i][0] = NUM;
			reduction_table[i][1] = EMPTY;
			reduction_table[i][2] = EMPTY;
			break;
		case 7:										// fact -> (expr)
			reduction_table[i][0] = LP;
			reduction_table[i][1] = EXPR;
			reduction_table[i][2] = RP;
			break;
		default:
			break;
		}
	}
}

static void push_value_stack(int val)
{
	value_stack_pos++;
	value_stack[value_stack_pos] = val;
}

static int pop_value_stack(void)
{
	int ret = value_stack[value_stack_pos];

	value_stack[value_stack_pos] = 0;
	value_stack_pos--;

	return ret;
}

static void init(void)
{
	int i;

	for (i = 0; i < PARSE_STACK_SIZE; i++)
		parse_stack[i] = EMPTY;

	init_reduction_table();
}