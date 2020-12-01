.global add_8bit_int
.global add_16bit_int

add_8bit_int:
	ldi r25, 0
	clc
	add r24, r22
	adc r25, r25

	ret

add_16bit_int:
	clc
	add r22, r24
	adc r23, r25
	ldi r24, 0
	adc r24, r24
	ldi r25, 0

	ret
