cmd_mw/unittest/amba_mw_unittest.lds := /usr/local/gcc-arm-none-eabi-4_9-2015q1/bin/arm-none-eabi-gcc -E -Wp,-MD,mw/unittest/.amba_mw_unittest.lds.d   -I/home/bingo/RD_A12/release_rtos/build/include -Ibuild/include -include /home/bingo/RD_A12/release_rtos/build/include/kconfig.h -I/home/bingo/RD_A12/release_rtos/bsp/dragonfly -mlittle-endian -DAMBA_KAL_NO_SMP -P -C -Uarm -D__ASSEMBLY__ -DLINKER_SCRIPT -o mw/unittest/amba_mw_unittest.lds /home/bingo/RD_A12/release_rtos/mw/unittest/amba_mw_unittest.lds.S

source_mw/unittest/amba_mw_unittest.lds := /home/bingo/RD_A12/release_rtos/mw/unittest/amba_mw_unittest.lds.S

deps_mw/unittest/amba_mw_unittest.lds := \
    $(wildcard build/include/config/soc/a12.h) \
    $(wildcard build/include/config/enable/virtual/address.h) \
    $(wildcard build/include/config/ambalink/mem/size.h) \
    $(wildcard build/include/config/cc/cxx/support.h) \
    $(wildcard build/include/config/ddr/size.h) \
  /home/bingo/RD_A12/release_rtos/build/include/kconfig.h \
    $(wildcard build/include/config/h.h) \
    $(wildcard build/include/config/.h) \
    $(wildcard build/include/config/booger.h) \
    $(wildcard build/include/config/foo.h) \

mw/unittest/amba_mw_unittest.lds: $(deps_mw/unittest/amba_mw_unittest.lds)

$(deps_mw/unittest/amba_mw_unittest.lds):