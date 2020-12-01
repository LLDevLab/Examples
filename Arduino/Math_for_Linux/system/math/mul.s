.global mul_8bit_int

mul_8bit_int:
	push r0
	push r1

	mul r24, r22

	mov r24, r0
	mov r25, r1

	pop r1
	pop r0

	ret
