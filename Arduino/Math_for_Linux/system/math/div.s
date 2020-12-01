.global div_16bit_int

div_16bit_int:
	push r16
	push r17
	push r18
	push r19
	push r20
	push r21

	clr r16
	clr r17

	mov r18, r24
	mov r19, r25

	ldi r20, 1
	clr r21

_div_16bit_int_loop:
	clc
	cp r18, r22
	cpc r19, r23

	brcs _div_16bit_int_exit

	sub r18, r22
	sbc r19, r23

	clc
	add r16, r20
	adc r17, r21
	rjmp _div_16bit_int_loop

_div_16bit_int_exit:
	mov r22, r18
	mov r23, r19
	mov r24, r16
	mov r25, r17

	pop r21
	pop r20
	pop r19
	pop r18
	pop r17
	pop r16
	ret
