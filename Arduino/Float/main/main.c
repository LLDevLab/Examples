#include "main.h"

extern uint32_t any2binary(float f);

int main(void)
{
	init();
	
	while(1)
	{
	}
	
	return 0;
}

static void init(void)
{
	float x = 13.375;
	uint32_t test = any2binary(x);
	
	uart_init();
	
	print_32bit_hex(test);
}
