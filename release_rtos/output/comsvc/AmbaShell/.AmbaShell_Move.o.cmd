cmd_comsvc/AmbaShell/AmbaShell_Move.o := /usr/local/gcc-arm-none-eabi-4_9-2015q1/bin/arm-none-eabi-gcc -Wp,-MD,comsvc/AmbaShell/.AmbaShell_Move.o.d   -I/home/bingo/RD_A12/release_rtos/build/include -Ibuild/include -include /home/bingo/RD_A12/release_rtos/build/include/kconfig.h -I/home/bingo/RD_A12/release_rtos/bsp/dragonfly  -I/home/bingo/RD_A12/release_rtos/comsvc/AmbaShell -Icomsvc/AmbaShell -mlittle-endian -DAMBA_KAL_NO_SMP -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Wno-format-security -fno-delete-null-pointer-checks -fshort-enums -fshort-wchar -D"SOC=KBUILD_STR(A12)" -O2 -fno-dwarf2-cfi-asm -mabi=aapcs-linux -mno-thumb-interwork -mfpu=vfpv3 -marm -march=armv7-a -mcpu=cortex-a9 -mhard-float -ffunction-sections -fdata-sections -Wno-missing-braces -fno-stack-protector -Wno-unused-but-set-variable -fomit-frame-pointer -fno-var-tracking-assignments -g -gdwarf-3 -Wdeclaration-after-statement -Wpointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -std=c99 -DCC_HAVE_ASM_GOTO -DAMBA_KAL_NO_SMP   -I/home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/comsvc/AmbaShell   -I/home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/comsvc/AmbaSys   -I/home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/comsvc/misc   -I/home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/prfile   -I/home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/fs   -I/home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/soc   -I/home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(AmbaShell_Move)"  -D"KBUILD_MODNAME=KBUILD_STR(libcomsvc_shell)" -c -o comsvc/AmbaShell/AmbaShell_Move.o /home/bingo/RD_A12/release_rtos/comsvc/AmbaShell/AmbaShell_Move.c

source_comsvc/AmbaShell/AmbaShell_Move.o := /home/bingo/RD_A12/release_rtos/comsvc/AmbaShell/AmbaShell_Move.c

deps_comsvc/AmbaShell/AmbaShell_Move.o := \
  /home/bingo/RD_A12/release_rtos/build/include/kconfig.h \
    $(wildcard build/include/config/h.h) \
    $(wildcard build/include/config/.h) \
    $(wildcard build/include/config/booger.h) \
    $(wildcard build/include/config/foo.h) \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/stdio.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/_ansi.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/newlib.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/sys/config.h \
    $(wildcard build/include/config/h//.h) \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/machine/ieeefp.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/sys/features.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/sys/cdefs.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/machine/_default_types.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/lib/gcc/arm-none-eabi/4.9.3/include/stddef.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/lib/gcc/arm-none-eabi/4.9.3/include/stdarg.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/sys/reent.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/_ansi.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/sys/_types.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/machine/_types.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/sys/lock.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/sys/types.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/machine/types.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/sys/stdio.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/string.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/sys/string.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/ctype.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/AmbaDataType.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/AmbaKAL.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/threadx/tx_api_Uniprocessor.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/threadx/tx_port_Uniprocessor.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/threadx/tx_user.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/stdlib.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/machine/stdlib.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/threadx/tx_execution_profile.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/comsvc/AmbaShell/AmbaShell.h \
    $(wildcard build/include/config/s/.h) \
    $(wildcard build/include/config/s.h) \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/fs/AmbaFS.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/fs/AmbaFS_Def.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/prfile2/pf_w_apicmn.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/prfile2/pf_apicmn.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/prfile2/pf_apicmn_def.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/prfile2/pf_config.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/prfile2/parts.cfg \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/prfile2/hardcfg.h \
    $(wildcard build/include/config/enable/exfat/support.h) \
    $(wildcard build/include/config/pf/character/code/set/cp932.h) \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/prfile2/pf_cfg_p.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/prfile2/pf_exfat_config.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/prfile2/pf_types.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/prfile2/e_types.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/inttypes.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/sys/_intsup.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/lib/gcc/arm-none-eabi/4.9.3/include/stdint.h \
  /usr/local/gcc-arm-none-eabi-4_9-2015q1/arm-none-eabi/include/stdint.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/prfile2/hardcfg.h \
  /home/bingo/RD_A12/release_rtos/vendors/ambarella/inc/ssp/prfile2/pf_exfat_apicmn.h \

comsvc/AmbaShell/AmbaShell_Move.o: $(deps_comsvc/AmbaShell/AmbaShell_Move.o)

$(deps_comsvc/AmbaShell/AmbaShell_Move.o):
