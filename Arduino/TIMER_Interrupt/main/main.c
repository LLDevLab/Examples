#include "main.h"

int main(void)
{
	init();
	
	while(1)
	{
	}
	
	// Отключаем глобальные прерывания
	cli();
	
	return 0;
}

static void init(void)
{
	// Настраиваем PORTB для мигания встроенным светодиодом
	DDRB = 0x20;
	
	// Настраиваем TIMER1 OVF прерывание
	init_timer1_ovf();
	
	// Включаем глобальные прерывания (по умолчанию все прерывания отключены)
	sei();
}

static void init_timer1_ovf(void)
{
	TCCR1A = 0x00;			// TCCR1A = Timer/Counter1 Control Register A
	TCCR1B = 0x05;			// Устанавливаем prescaler 1024 (TCCR1B = Timer/Counter1 Control Register B)
	
	// Очищаем флаг, обозначающий срабатывание OVF1 прерывания
	TIFR1 |= 0x01;			// TIFR1 = Timer/Counter1 Interrupt flag register
	
	// Устанавливаем значение счетчика
	TCNT1 = 0x0000;
	
	// Включаем прерывание OVF1
	TIMSK1 = 0x01;			// TIMSK1 = Timer/Counter1 Interrupt Mask Register
}

void timer1_ovf_isr(void)
{
	// Мигаем встроенным светодиодом
	PORTB ^= 0x20;
}
