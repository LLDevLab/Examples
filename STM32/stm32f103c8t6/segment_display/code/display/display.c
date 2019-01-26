#include "display.h"

void display_init(void (*send_data)(uint8_t dig, uint8_t value))
{
	display_send_data = send_data;
}

/*
digit_pos - Позиция знака на дисплее (1, 2, 3, 4)
digit_value - Цифра которую надо отобразить (0 - 9)
*/
void display_digit(uint8_t digit_pos, uint8_t digit_value)
{
	uint8_t pos;
	uint8_t show_segs;
	
	pos	= get_disp_pos(digit_pos);
	show_segs = val_to_seg(digit_value);
	
	(*display_send_data)(pos, show_segs);	// Вызываем функцию, которая отобразит изменения на дисплее
}

// Конвертирует десятичное число, в бинарный код позиции 
static uint8_t get_disp_pos(uint8_t pos)
{
	enum disp_pos ret;
	
	switch(pos)
	{
		case 1:
			ret = POS_1;
			break;
		case 2:
			ret = POS_2;
			break;
		case 3:
			ret = POS_3;
			break;
		case 4:
			ret = POS_4;
			break;
		default:
			break;
	}
	
	return (uint8_t)ret;
}

// Конвертирует десятичное число, в бинарное значения обозначающее какой сегмент должен загореться
// В бинарном коде 0 — сегмент горит, 1 — не горит
static uint8_t val_to_seg(uint8_t value)
{
	uint8_t ret;
	
	switch(value)
	{
		case 1:
			ret = SEG_2 & SEG_3;
			break;
		case 2:
			ret = SEG_1 & SEG_2 & SEG_7 & SEG_5 & SEG_4;
			break;
		case 3:
			ret = SEG_1 & SEG_2 & SEG_7 & SEG_3 & SEG_4;
			break;
		case 4:
			ret = SEG_6 & SEG_2 & SEG_7 & SEG_3;
			break;
		case 5:
			ret = SEG_1 & SEG_6 & SEG_7 & SEG_3 & SEG_4;
			break;
		case 6:
			ret = SEG_1 & SEG_6 & SEG_7 & SEG_5 & SEG_3 & SEG_4;
			break;
		case 7:
			ret = SEG_1 & SEG_2 & SEG_3;
			break;
		case 8:
			ret = SEG_1 & SEG_2 & SEG_3 & SEG_4 & SEG_5 & SEG_6 & SEG_7;
			break;
		case 9:
			ret = SEG_1 & SEG_2 & SEG_3 & SEG_4 & SEG_6 & SEG_7;
			break;
		default:
			ret = SEG_1 & SEG_2 & SEG_3 & SEG_4 & SEG_5 & SEG_6;
			break;
	}
	
	return ret;
}