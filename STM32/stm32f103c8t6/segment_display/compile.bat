cls
"D:\ARM_Toolchain\gcc-arm-none-eabi-6-2017-q2-update-win32\bin\arm-none-eabi-as" -c -mcpu=cortex-m3 .\code\system\startup.s -o .\tmp\startup.o
"D:\ARM_Toolchain\gcc-arm-none-eabi-6-2017-q2-update-win32\bin\arm-none-eabi-gcc" -c -mcpu=cortex-m3 --specs=nosys.specs .\code\display\display.c -o .\tmp\display.o
"D:\ARM_Toolchain\gcc-arm-none-eabi-6-2017-q2-update-win32\bin\arm-none-eabi-gcc" -mcpu=cortex-m3 --specs=nosys.specs .\tmp\startup.o .\tmp\display.o .\code\system\main.c -T stm32f103c8t6_link_map.ld -static -nostartfiles -o .\tmp\main.elf
"D:\ARM_Toolchain\gcc-arm-none-eabi-6-2017-q2-update-win32\bin\arm-none-eabi-objcopy" -O binary .\tmp\main.elf main.bin

