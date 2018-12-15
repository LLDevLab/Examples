@ Все Cortex-M процессоры используют thumb инструкции, так что включаем thumb режим
.thumb

@ В связи с тем, что ARM ассемблер может выполнять 2 типа инструкций (arm и thumb), то компилятор поддерживает 2 синтаксиса для работы с ними 
@ (подробнее можно почитать тут:  https://sourceware.org/binutils/docs/as/ARM_002dInstruction_002dSet.html#ARM_002dInstruction_002dSet
.syntax unified

.equ STACKINIT, 0x20005000		@ Определяем адрес конца SRAM

@ Начало секции кода
.text

@ Начало вектора прерываний
SP: .word STACKINIT					@ Первая запись в векторе прерываний — это адрес вершины стэка. Процессор в начале работы инициализирует SP регистр этим адресом
RESET: .word main					@ Reset вектор
@ Далее идут высоко приоритетные прерывания которые обязательно должны присутствовать в векторе прерываний. Подробнее о них можно почитать сдесь:
@ http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0553a/BABBGBEC.html
NMI_HANDLER: .word nmi_fault		
HARD_FAULT: .word hard_fault		
MEMORY_FAULT: .word memory_fault
BUS_FAULT: .word bus_fault
@ Так как thumb и arm наборы инструкции имеют разный сдвиг адреса, чтобы обеспечить корректную работу всех thumb инструкций 
@ прибавляем к последнему адресу вектора прерываний 1. Подробнее про thumb и arm наборы инструкций можно почитать сдесь:
@ http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0473j/dom1359731139853.html
USAGE_FAULT: .word usage_fault + 1

@ Включаем код из led.inc в main.s, если он не был включен раньше
.ifndef LED_DEF
.include "stm32f103c8t6_core/led.inc"
.endif

main:
	push {lr}					@ Сохраняем Link Register в стэк
	bl led_init					@ Вызываем функцию led_init
	pop {lr}					@ Восстанавливаем Link Register из стэка
	
_main_loop:						@ Главный цикл программы
	push {lr}					@ Сохраняем Link Register в стэк
	bl led_flash				@ Вызываем функцию led_flash
	bl wait						@ Вызываем функцию wait
	pop {lr}					@ Восстанавливаем Link Register из стэка
	b _main_loop				@ Безусловный переход на метку _main_loop
	
	bx lr						@ Безусловный переход по адресу из Link Register (выход из функции)

@ Функция активного ожидания
wait:
	push {r0}					@ Сохраняем регистр r0 в стэк
	
	ldr r0, =0xFFFF0			@ Загружаем в r0 число 0xFFFF0 (0xFFFF0 будет хранится в памяти как константа)
_wait_loop:						@ Метка цикла ожидания
	subs r0, r0, 1				@ Вычитаем из r0 единицу
	bne _wait_loop				@ Переходим на метку _wait_loop, если в результате вычитания Zero flag не был выставлен в 1 (т. е. результат вычитания не равен нулю)
		
	pop {r0}					@ Восстанавливаем r0 из стэка				
	bx lr						@ Выходим из функции

nmi_fault:
	@ breakpoint
	bkpt
	bx lr
	
hard_fault:
	@ breakpoint
	bkpt
	bx lr

memory_fault:
	@ breakpoint
	bkpt
	bx lr

bus_fault:
	@ breakpoint
	bkpt
	bx lr

usage_fault:
	@ breakpoint
	bkpt
	bx lr	
	
.end
	