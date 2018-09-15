#include "main.h"

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
	uart_init();
	printHelloWorld();
}

static void printHelloWorld(void)
{
	char arr[] = "Hello world!";
	uint8_t len = 12;
	uint8_t i;
	
	for(i = 0; i < len; i++)
	{
		uart_transmit(arr[i]);
	}
}
