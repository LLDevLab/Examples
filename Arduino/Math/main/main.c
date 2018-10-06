#include "main.h"

extern uint16_t add_8bit_int(uint8_t param1, uint8_t param2);
extern uint32_t add_16bit_int(uint16_t param1, uint16_t param2);
extern uint16_t sub_16bit_int(uint16_t param1, uint16_t param2);

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
	uint16_t res16 = 0;
	uint32_t res32 = 0;
	
	uart_init();
	
	res16 = add_8bit_int(255, 255);
	print_16bit_hex(res16);
	
	uart_transmit(' ');
	
	res32 = add_16bit_int(0xFFFF, 0xFFFF);
	print_32bit_hex(res32);
	
	uart_transmit(' ');
	
	res16 = sub_16bit_int(300, 275);
	print_16bit_hex(res16);
}
