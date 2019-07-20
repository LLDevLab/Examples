#include "parser.h"

static int parse_table[PARSE_TABLE_ROWS][PARSE_TABLE_COLS];
static int todo_table[TODO_TABLE_ROW_LEN][TODO_TABLE_COL_LEN];
static int parse_stack[PARSE_STACK_SIZE];
static int value_stack[VALUE_STACK_SIZE];
static int parse_stack_index = -1;
static int value_stack_index = -1;

int parse_input(char* input_str)
{
	token_lexeme token;
	int val1 = 0, val2 = 0;
	int top_of_stack;
	int action = 0;
	int parse_table_index;

	init();

	set_input_stream(input_str);

	token = get_next_token();

	if (token.token == UNKNOWN)
		return val1;

	parse_stack_push(STMT);

	while (parse_stack_index >= 0)
	{
		if (parse_stack[parse_stack_index] >= PLUS_ACT)
		{
			// Обработка действий			
			switch (parse_stack[parse_stack_index])
			{
			case PLUS_ACT:
				val1 = value_stack_pop();
				val2 = value_stack_pop();
				val1 += val2;
				value_stack_push(val1);
				break;
			case STAR_ACT:
				val1 = value_stack_pop();
				val2 = value_stack_pop();
				val1 *= val2;
				value_stack_push(val1);
				break;
			default:
				break;
			}

			parse_stack_pop();
		}
		else if(parse_stack[parse_stack_index] >= STMT)
		{
			// Обработка nonterminal символов
			top_of_stack = parse_stack_pop();

			parse_table_index = nonterminal_to_index(top_of_stack);

			action = parse_table[parse_table_index][token.token];

			if (action < 0)
				// error
				break;
			else
				parse_stack_substitute(action);
		}
		else
		{
			// Обработка terminal символов
			top_of_stack = parse_stack_pop();

			if (top_of_stack < 0)
				// error
				break;

			if (top_of_stack != token.token)
				// error
				break;
			else
			{
				if (token.token == NUM)
					value_stack_push(atoi(&token.lexeme));

				token = get_next_token();
			}
		}
	}

	return value_stack_pop();
}

static void init(void)
{
	int i;

	for (i = 0; i < PARSE_STACK_SIZE; i++)
		parse_stack[i] = ERROR;

	for (i = 0; i < VALUE_STACK_SIZE; i++)
		value_stack[i] = 0;

	init_parse_table();
	init_todo_table();
}

static enum NONTERMINALS index_to_nonterminal(int index)
{
	return index + STMT;
}

static int nonterminal_to_index(enum NONTERMINALS nonterm)
{
	return nonterm - STMT;
}

static void init_parse_table(void)
{
	int row, col;
	enum NONTERMINALS nonterm_sym;

	for (row = 0; row < PARSE_TABLE_ROWS; row++)
	{
		nonterm_sym = index_to_nonterminal(row);

		for (col = 0; col < PARSE_TABLE_COLS; col++)
		{
			switch (nonterm_sym)
			{
			case STMT:
				switch (col)
				{				
				case NUM:
				case LP:
					parse_table[row][col] = 0;				// stmt -> expr
					break;
				case EOI:
					parse_table[row][col] = 7;				// stmt -> epsilon
					break;
				default:
					parse_table[row][col] = ERROR;
					break;
				}
				break;
			case EXPR:
				switch (col)
				{
				case NUM:
				case LP:
					parse_table[row][col] = 1;				// expr -> term expr'
					break;			
				default:
					parse_table[row][col] = ERROR;
					break;
				}
				break;
			case EXPR_PRIME:
				switch (col)
				{
				case PLUS:
					parse_table[row][col] = 2;				// expr' -> + term expr'
					break;	
				default:
					parse_table[row][col] = 7;				// expr' -> epsilon
					break;
				}
				break;
			case TERM:
				switch (col)
				{
				case LP:
				case NUM:
					parse_table[row][col] = 3;				// term -> fact term'
					break;
				default:
					parse_table[row][col] = ERROR;
					break;
				}
				break;
			case TERM_PRIME:
				switch (col)
				{
				case STAR:
					parse_table[row][col] = 4;				// term' -> * fact term'
					break;
				default:
					parse_table[row][col] = 7;				// term' -> epsilon
					break;
				}
				break;
			case FACT:
				switch (col)
				{
				case NUM:
					parse_table[row][col] = 5;				// fact -> num
					break;
				case LP:
					parse_table[row][col] = 6;				// fact -> (expr)
					break;
				default:
					parse_table[row][col] = ERROR;
					break;
				}
				break;
			}
		}
	}
}

static void init_todo_table(void)
{
	int i, j;

	// Инициализирую элементы в обратном порядке
	for (i = 0; i < TODO_TABLE_ROW_LEN; i++)
	{
		for (j = 0; j < TODO_TABLE_COL_LEN; j++)
		{
			switch (i)
			{
			case 0:					// stmt
				switch (j)
				{
				case 0:
					todo_table[i][j] = EXPR;
					break;
				default:
					todo_table[i][j] = EMPTY;
					break;
				}
				break;
			case 1:					// expr
				switch (j)
				{
				case 0:
					todo_table[i][j] = EXPR_PRIME;
					break;
				case 1:
					todo_table[i][j] = TERM;
					break;
				default:
					todo_table[i][j] = EMPTY;
					break;
				}
				break;
			case 2:					// expr'
				switch (j)
				{
				case 0:					
					todo_table[i][j] = PLUS_ACT;
					break;
				case 1:
					todo_table[i][j] = EXPR_PRIME;
					break;
				case 2:
					todo_table[i][j] = TERM;
					break;
				default:
					todo_table[i][j] = PLUS;
					break;
				}
				break;
			case 3:					// term
				switch (j)
				{
				case 0:
					todo_table[i][j] = TERM_PRIME;
					break;
				case 1:
					todo_table[i][j] = FACT;
					break;
				default:
					todo_table[i][j] = EMPTY;
					break;
				}
				break;
			case 4:					// term'
				switch (j)
				{
				case 0:
					todo_table[i][j] = STAR_ACT;
					break;					
				case 1:
					todo_table[i][j] = TERM_PRIME;
					break;
				case 2:
					todo_table[i][j] = FACT;
					break;
				default:
					todo_table[i][j] = STAR;
					break;
				}
				break;
			case 5:					// fact to NUM
				switch (j)
				{
				case 0:
					todo_table[i][j] = NUM;
					break;
				default:
					todo_table[i][j] = EMPTY;
					break;
				}
				break;
			case 6:					// fact to (expr)
				switch (j)
				{
				case 0:
					todo_table[i][j] = RP;
					break;
				case 1:
					todo_table[i][j] = EXPR;
					break;
				case 2:
					todo_table[i][j] = LP;
					break;
				default:
					todo_table[i][j] = EMPTY;
					break;
				}
				break;
			case 7:					// epsilon 
				todo_table[i][j] = EMPTY;
				break;
			}
		}
	}
}

static int parse_stack_pop(void)
{
	int ret;
	
	if (parse_stack_index < 0)
		return -1;

	ret = parse_stack[parse_stack_index];

	parse_stack[parse_stack_index] = ERROR;
	parse_stack_index--;

	return ret;
}

static void parse_stack_push(int value)
{
	parse_stack_index++;
	parse_stack[parse_stack_index] = value;
}

static void parse_stack_substitute(int value)
{
	int i;

	for (i = 0; i < TODO_TABLE_COL_LEN; i++)
	{
		if (todo_table[value][i] >= 0)
			parse_stack_push(todo_table[value][i]);
	}
}

static void value_stack_push(int value)
{
	value_stack_index++;
	value_stack[value_stack_index] = value;
}

static int value_stack_pop(void)
{
	int ret = 0;

	if (value_stack_index < 0)
		return 0;

	ret = value_stack[value_stack_index];

	value_stack[value_stack_index] = 0;
	value_stack_index--;

	return ret;
}