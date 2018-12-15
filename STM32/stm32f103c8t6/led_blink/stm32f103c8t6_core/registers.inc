STM32F103C8T6_REGISTERS = 0 

.ifndef STM32F103C8T6_PORT_CODES
.include "stm32f103c8t6_core/memory_mapping.inc"
.endif	

.equ RCC_CR, RCC + 0x00				@ clock control register
.equ RCC_CFGR, RCC + 0x04			@ clock configuration register
.equ RCC_CIR, RCC + 0x08			@ clock interrupt register
.equ RCC_APB2RSTR, RCC + 0x0C		@ APB2 peripherial reset register (APB - advanced peripherial bus)
.equ RCC_APB1RSTR, RCC + 0x10		@ APB1 peripherial reset register
.equ RCC_AHBENR, RCC + 0x14			@ AHB peripherial clock enable register (AHB - advanced high performance bus)
.equ RCC_APB2ENR, RCC + 0x18		@ APB2 peripherial clock enable register
.equ RCC_APB1ENR, RCC + 0x1C		@ APB1 peripherial clock enable register
.equ RCC_BDCR, RCC + 0x20			@ backup domain control register	
.equ RCC_CSR, RCC + 0x24			@ control/status register

.equ GPIOC_CRL, PORT_C				@ port C control register low
.equ GPIOC_CRH, PORT_C + 0x04		@ port C control register high
.equ GPIOC_IDR, PORT_C + 0x08		@ port C input data register
.equ GPIOC_ODR, PORT_C + 0x0C		@ port C output data register
.equ GPIOC_BSRR, PORT_C + 0x10		@ port C bit set/reset register
.equ GPIOC_BRR, PORT_C + 0x14		@ port C bit reset register (16 bit)
.equ GPIOC_LCKR, PORT_C + 0x18		@ port C configuration lock register
