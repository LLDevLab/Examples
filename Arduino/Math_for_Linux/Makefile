TOOLS_PATH = /home/ja/Downloads/arduino-1.8.13/hardware/tools/avr/bin
AS = $(TOOLS_PATH)/avr-as
CC = $(TOOLS_PATH)/avr-gcc
PARAMS = -g -mmcu=atmega328p
SYS_MATH = system/math

main.elf: math.o
	$(CC) $(PARAMS) main/main.c tmp/math.o -o tmp/main.elf

math.o:
	$(AS) $(PARAMS) $(SYS_MATH)/add.s $(SYS_MATH)/sub.s $(SYS_MATH)/mul.s $(SYS_MATH)/div.s -o tmp/math.o

clean:
	rm -f tmp/*