cls
"D:\Arduino\arduino_1.8.3\hardware\tools\avr\bin\avr-gcc" -mmcu=atmega328p main\main.c system\uart\uart.c -o tmp\main.elf
"D:\Arduino\arduino_1.8.3\hardware\tools\avr\bin\avr-objcopy" -O ihex -R .eeprom tmp\main.elf main.hex

