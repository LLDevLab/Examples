#ifndef  _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../LexAnalyzer/lex_analyzer.h"

#define EMPTY -1

#define PARSE_STACK_SIZE 10
#define VALUE_STACK_SIZE 10

#define REDUCTION_TABLE_ROWS 8
#define REDUCTION_TABLE_COLS 3

int parse_input(char* input_str);

static void init(void);
static void shift(token_lexeme* token);
static void reduce(int table_index);
static void init_reduction_table(void);
static void push_value_stack(int val);
static int pop_value_stack(void);

#endif 
