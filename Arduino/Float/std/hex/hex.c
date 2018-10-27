#include "hex.h"

char hex2char(uint8_t value)
{
	switch(value)
	{
		case 0 ... 9:
			return value | 0x30;
		case 10:
			return 'A';
		case 11:
			return 'B';
		case 12:
			return 'C';
		case 13:
			return 'D';
		case 14:
			return 'E';
		case 15:
			return 'F';
		default:
			return 0;
	}
}