.thumb
.syntax unified

.equ STACKINIT, 0x20005000

.extern _data_flash
.extern _sdata
.extern _edata

.text

SP: .word STACKINIT
RESET: .word _main
NMI_HANDLER: .word _nmi_fault
HARD_FAULT: .word _hard_fault
MEMORY_FAULT: .word _memory_fault
BUS_FAULT: .word _bus_fault
USAGE_FAULT: .word _usage_fault + 1

_main:
	push {lr}
	bl _data_copy
	bl main
	pop {lr}
	bx lr
	
_data_copy:
	push {r0, r1, r2, r3 }
	ldr r0, =_data_flash
	ldr r1, =_sdata
	ldr r2, =_edata
_data_copy_loop:
	ldr r3, [r0]
	str r3, [r1]
	add r1, #4
	add r0, #4
	cmp r1, r2
	blt _data_copy_loop
	
	pop { r0, r1, r2, r3 }
	bx lr

_nmi_fault:
	@ breakpoint
	bkpt
	bx lr

_hard_fault:
	@ breakpoint
	bkpt
	bx lr

_memory_fault:
	@ breakpoint
	bkpt
	bx lr

_bus_fault:
	@ breakpoint
	bkpt
	bx lr

_usage_fault:
	@ breakpoint
	bkpt
	bx lr

.end
