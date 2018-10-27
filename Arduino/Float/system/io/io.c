#include "io.h"

void print_16bit_hex(uint16_t value)
{
	uint8_t i, j;
	uint8_t arr_len = 6;
	char print_arr[arr_len];
	uint8_t print_val;
	uint8_t shift_len = 16;
	uint8_t arr_cnt = 2;
	
	print_arr[0] = '0';
	print_arr[1] = 'x';
	
	do
	{
		shift_len -= 8;
		print_val = value >> shift_len;	
		print_arr[arr_cnt] = hex2char((uint8_t)print_val >> 4);
		print_arr[arr_cnt + 1] = hex2char((uint8_t)print_val & 0x0F);
		arr_cnt += 2;
	}
	while(shift_len != 0);
	
	for(i = 0; i < arr_len; i++)
	{
		uart_transmit(print_arr[i]);
	}
}

void print_32bit_hex(uint32_t value)
{
	uint8_t i;
	uint8_t arr_len = 10;
	char print_arr[arr_len];
	uint8_t print_val;
	uint8_t shift_len = 32;
	uint8_t arr_cnt = 2;
	
	print_arr[0] = '0';
	print_arr[1] = 'x';
	
	do
	{
		shift_len -= 8;
		print_val = value >> shift_len;	
		print_arr[arr_cnt] = hex2char((uint8_t)print_val >> 4);
		print_arr[arr_cnt + 1] = hex2char((uint8_t)print_val & 0x0F);
		arr_cnt += 2;
	}
	while(shift_len != 0);
	
	for(i = 0; i < arr_len; i++)
	{
		uart_transmit(print_arr[i]);
	}
}