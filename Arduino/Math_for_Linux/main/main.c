#include "main.h"

extern uint16_t mul_8bit_int(uint8_t param1, uint8_t param2);
extern uint32_t div_16bit_int(uint16_t param1, uint16_t param2);

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

	res16 = mul_8bit_int(100, 9);
	res32 = div_16bit_int(1589, 38);
}
