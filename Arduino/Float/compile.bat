cls
"D:\Arduino\arduino_1.8.3\hardware\tools\avr\bin\avr-as" -mmcu=atmega328p std\any\any.s -o tmp\any.o
"D:\Arduino\arduino_1.8.3\hardware\tools\avr\bin\avr-gcc" -c -mmcu=atmega328p system\uart\uart.c -o tmp\uart.o
"D:\Arduino\arduino_1.8.3\hardware\tools\avr\bin\avr-gcc" -c -mmcu=atmega328p system\io\io.c -o tmp\io.o
"D:\Arduino\arduino_1.8.3\hardware\tools\avr\bin\avr-gcc" -c -mmcu=atmega328p std\hex\hex.c -o tmp\hex.o
"D:\Arduino\arduino_1.8.3\hardware\tools\avr\bin\avr-gcc" -mmcu=atmega328p main\main.c tmp\uart.o tmp\io.o tmp\hex.o tmp\any.o -o tmp\main.elf
"D:\Arduino\arduino_1.8.3\hardware\tools\avr\bin\avr-objcopy" -O ihex -R .eeprom tmp\main.elf main.hex