#include "memory_mapping.h"

// reset and clock cotrol registers
#define RCC_CR 			(*((volatile uint32_t*)(RCC + 0x00)))					// clock control register
#define RCC_CFGR 		(*((volatile uint32_t*)(RCC + 0x04)))					// clock configuration register
#define RCC_CIR 		(*((volatile uint32_t*)(RCC + 0x08)))					// clock interrupt register
#define RCC_APB2RSTR 	(*((volatile uint32_t*)(RCC + 0x0C)))					// APB2 peripherial reset register (APB - advanced peripherial bus)
#define RCC_APB1RSTR 	(*((volatile uint32_t*)(RCC + 0x10)))					// APB1 peripherial reset register
#define RCC_AHBENR 		(*((volatile uint32_t*)(RCC + 0x14)))					// AHB peripherial clock enable register (AHB - advanced high performance bus)
#define RCC_APB2ENR 	(*((volatile uint32_t*)(RCC + 0x18)))					// APB2 peripherial clock enable register
#define RCC_APB1ENR 	(*((volatile uint32_t*)(RCC + 0x1C)))					// APB1 peripherial clock enable register
#define RCC_BDCR 		(*((volatile uint32_t*)(RCC + 0x20)))					// backup domain control register	
#define RCC_CSR 		(*((volatile uint32_t*)(RCC + 0x24)))					// control/status register

// GPIO port C registers
#define GPIOC_CRL 		(*((volatile uint32_t*)(PORT_C + 0x00)))				// port C control register low
#define GPIOC_CRH 		(*((volatile uint32_t*)(PORT_C + 0x04)))				// port C control register high
#define GPIOC_IDR 		(*((volatile uint32_t*)(PORT_C + 0x08)))				// port C input data register
#define GPIOC_ODR 		(*((volatile uint32_t*)(PORT_C + 0x0C)))				// port C output data register
#define GPIOC_BSRR 		(*((volatile uint32_t*)(PORT_C + 0x10)))				// port C bit set/reset register
#define GPIOC_BRR 		(*((volatile uint32_t*)(PORT_C + 0x14)))				// port C bit reset register (16 bit)
#define GPIOC_LCKR 		(*((volatile uint32_t*)(PORT_C + 0x18)))				// port C configuration lock register
