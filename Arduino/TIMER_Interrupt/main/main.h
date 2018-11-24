// этот загаловок всегда стоит включать при программировании Arduino на Си
// в он среди прочего включает в себя адреса регистров Arduino 
// так что нам не придеться дефинировать их самостоятельно
#include <avr/io.h>	
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 16000000UL    
#endif

static void init(void);
static void init_timer1_ovf(void);

void timer1_ovf_isr(void);
