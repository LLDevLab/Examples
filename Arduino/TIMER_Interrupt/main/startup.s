.equ _SREG, 0x3F							; Адрес SREG регистра
.equ _SPL, 0x3D								; Stack Pointer Low Register
.equ _SPH, 0x3E								; Stack Pointer High Register

.text
.org 0x0000
; Так как длинна инструкции jmp - 2 процессорных слова, то каждая последующая инструкция будет иметь сдвиг +2 относительно адреса предыдущей инструкции
jmp _main									; 0x0000 	reset vector
jmp _return_from_interrupt					; 0x0002
jmp _return_from_interrupt					; 0x0004
jmp _return_from_interrupt					; 0x0006
jmp _return_from_interrupt					; 0x0008
jmp _return_from_interrupt					; 0x000A
jmp _return_from_interrupt					; 0x000C		
jmp _return_from_interrupt					; 0x000E
jmp _return_from_interrupt					; 0x0010
jmp _return_from_interrupt					; 0x0012
jmp _return_from_interrupt					; 0x0014
jmp _return_from_interrupt					; 0x0016
jmp _return_from_interrupt					; 0x0018
jmp _timer1_ovf_isr							; 0x001A	timer1 overflow interrupt
jmp _return_from_interrupt					; 0x001C
jmp _return_from_interrupt					; 0x001E
jmp _return_from_interrupt					; 0x0020		
jmp _return_from_interrupt					; 0x0022	
jmp _return_from_interrupt					; 0x0024
jmp _return_from_interrupt					; 0x0026	
jmp _return_from_interrupt					; 0x0028
jmp _return_from_interrupt					; 0x002A
jmp _return_from_interrupt					; 0x002C
jmp _return_from_interrupt					; 0x002E
jmp _return_from_interrupt					; 0x0030
jmp _return_from_interrupt					; 0x0032

_return_from_interrupt:
	reti
	
_main:
	; Стандартный код загрузки (убранный опцией -nostartfiles) среди прочего делал следущее:
	; Обнулял статус регистр
	ldi r20, 0
	sts _SREG, r20
	
	; Устанавливал текущий адрес стека в конец оперативной памяти (0x800 или 2048 byte SRAM в Atmega328p)
	sts _SPL, r20
	ldi r20, 0x08
	sts _SPH, r20
	
	; вызываем Cи функцию main
	call main
	reti

_timer1_ovf_isr:
	push r20
	
	; сохраняем значения всех флагов (SREG регистра) до того как что-то делать в обработчике прерывания 
	lds r20, _SREG
	push r20
	
	; вызываем Cи функцию обработчик прерывания
	call timer1_ovf_isr
	
	; Восстанавливаем значение флагов (SREG регистра), которое было до вызова прерывания
	pop r20
	sts _SREG, r20
	
	; Восстанавливаем изначальное значение регистра r20
	pop r20
	
	; Выходим из обработчика прерывания
	reti
	