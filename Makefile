CC = xtensa-lx106-elf-gcc
AR = xtensa-lx106-elf-ar
CFLAGS = -I. -Os -mlongcalls -ffunction-sections -fdata-sections

libnewlibport.a: newlib_port.o
	$(AR) cru $@ $^

newlib_port.o : newlib_port.c

clean:
	rm -f newlib_port.o libnewlibport.a