CC = xtensa-esp108-elf-gcc
AR = xtensa-esp108-elf-ar
SYSROOT_HEADERS = $(shell $(CC) --print-sysroot)/usr/include
CFLAGS = -I. -Os -mlongcalls -ffunction-sections -fdata-sections \
            -I$(SYSROOT_HEADERS)/lwip         \
            -I$(SYSROOT_HEADERS)/lwip/ipv4    \
            -I$(SYSROOT_HEADERS)/lwip/ipv6    \
            -I$(SYSROOT_HEADERS)/espressif    

libnewlibport.a: newlib_port.o
	$(AR) cru $@ $^

newlib_port.o : newlib_port.c

clean:
	rm -f newlib_port.o libnewlibport.a
