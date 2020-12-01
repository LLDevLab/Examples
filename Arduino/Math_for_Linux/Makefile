TOOLS_PATH = /home/ja/Downloads/arduino-1.8.13/hardware/tools/avr/bin
AS = $(TOOLS_PATH)/avr-as
CC = $(TOOLS_PATH)/avr-gcc
PARAMS = -g -mmcu=atmega328p
SYS_MATH = system/math

main.elf: hex.o io.o uart.o math.o
	$(CC) $(PARAMS) main/main.c tmp/hex.o tmp/io.o tmp/uart.o tmp/math.o -o tmp/main.elf

hex.o:
	$(CC) $(PARAMS) -c std/hex/hex.c -o tmp/hex.o

io.o:
	$(CC) $(PARAMS) -c system/io/io.c -o tmp/io.o

uart.o:
	$(CC) $(PARAMS) -c system/uart/uart.c -o tmp/uart.o

math.o:
	$(AS) $(PARAMS) $(SYS_MATH)/add.s $(SYS_MATH)/sub.s $(SYS_MATH)/mul.s $(SYS_MATH)/div.s -o tmp/math.o

clean:
	rm -f tmp/*