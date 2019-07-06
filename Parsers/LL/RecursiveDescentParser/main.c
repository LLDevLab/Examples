#include "Parser/parser.h"

int main(int argc, char** argv)
{
	parse_input(argv[1] + '\0');
	return 0;
}
