#ifndef _PRINT_H_
#define _PRINT_H_

#include "../uart/uart.h"
#include "../../std/hex/hex.h"

void print_16bit_hex(uint16_t value);
void print_32bit_hex(uint32_t value);

#endif