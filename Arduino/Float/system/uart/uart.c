#include "uart.h"

void uart_init(void)
{	
	// UBRR0H = USART0 Baud Rate Register High
	// UBRR0L = USART0 Baud Rate Register Low
	// Устанавливаем prescaler в регистры
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	
	// UCSR0B = USART0 Control and Status Register B
	// TXEN0 = (USART0) Transmitter Enable bit (бит 3)
	// Включаем UART передатчик
	UCSR0B |= (1 << TXEN0);						
}

void uart_transmit(uint8_t data)
{
	// UCSR0A = USART0 Control and Status Register A
	// UDR0 = USART0 Data Register
	// UDRE0 = USART0 Data Register Empty bit (бит 5)
	// Цикл будет выполняться до тех пор, пока UDRE0 бит в регистре UCSR0A не будет равен единице 
	// Микроконтроллер записывает в этот бит единицу, когда буфер UDR0 готов принимать новые данные 
	while(!(UCSR0A & (1 << UDRE0)));
	
	// UDR = USART0 Data Register
	UDR0 = data;
}