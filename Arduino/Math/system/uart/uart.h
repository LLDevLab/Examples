#ifndef _UART_H_
#define _UART_H_

#include <avr/io.h>  
#define F_CPU 16000000UL    
#define BAUD 9600
#include <util/setbaud.h>

void uart_init(void);
void uart_transmit(uint8_t data);
#endif

