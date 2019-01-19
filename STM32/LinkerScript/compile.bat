cls
"D:\ARM_Toolchain\gcc-arm-none-eabi-6-2017-q2-update-win32\bin\arm-none-eabi-as" -c -g -mcpu=cortex-m3 .\code\startup.s -o .\tmp\startup.o
"D:\ARM_Toolchain\gcc-arm-none-eabi-6-2017-q2-update-win32\bin\arm-none-eabi-gcc" -mcpu=cortex-m3 -c .\code\main.c -o .\tmp\main.o
"D:\ARM_Toolchain\gcc-arm-none-eabi-6-2017-q2-update-win32\bin\arm-none-eabi-gcc" -mcpu=cortex-m3 .\tmp\startup.o .\tmp\main.o -T stm32f103c8t6_link_map.ld -nostartfiles -o .\tmp\main.elf
"D:\ARM_Toolchain\gcc-arm-none-eabi-6-2017-q2-update-win32\bin\arm-none-eabi-objcopy" -O binary .\tmp\main.elf main.bin

