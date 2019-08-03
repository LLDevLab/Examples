#include "Parser/parser.h"

int main(int argc, char** argv)
{
	int result;

	result = parse_input(argv[1] + '\0');

	printf("Result: %d\n", result);
	return 0;
}
