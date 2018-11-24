cls
"D:\Arduino\arduino_1.8.3\hardware\tools\avr\bin\avr-as" -mmcu=atmega328p main\startup.s -o tmp\startup.o
:: NB! tmp\startup.o должен идти перед main\main.c иначе программа соберется не правильно!
:: -nostartfiles - Исключает из компиляции стандартный код загрузки
"D:\Arduino\arduino_1.8.3\hardware\tools\avr\bin\avr-gcc" -mmcu=atmega328p tmp\startup.o main\main.c -nostartfiles -o tmp\main.elf
"D:\Arduino\arduino_1.8.3\hardware\tools\avr\bin\avr-objcopy" -O ihex -R .eeprom tmp\main.elf main.hex