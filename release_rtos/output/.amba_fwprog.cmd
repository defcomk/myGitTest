cmd_amba_fwprog := /bin/bash /home/bingo/RD_A12/release_rtos/ssp/fwprog/link-amba_fwprog.sh /usr/local/gcc-arm-none-eabi-4_9-2015q1/bin/arm-none-eabi-ld -EL  -p --no-undefined --gc-sections --no-wchar-size-warning -nostdlib -nodefaultlibs -nostartfiles -L/usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/lib/armv7-ar/thumb/fpu -L/usr/local/gcc-arm-none-eabi-4_9-2015q1/lib/gcc/arm-none-eabi/4.9.3/armv7-ar/thumb/fpu
