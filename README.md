# esp_newlib_port
Provides to newlib memory management routines and syscalls based on Espressif SDK memory functions.

## [Why] Do i really need it?
The libc implementation called newlib which is built by crosstool-ng shall somehow be connected to the target hardware platform. The integration is done through a set of functions called syscalls. Operating system (or whatever) shall provide implementation for these syscalls. The lib contains syscalls based on Espressif non-OS SDK for ESP8266.
The lib also contains implementation of memory management routines. Espressif SDK already has memory management functions. Making newlib's and SDK's memory management coexist seems to be impossible. So the lib provides memory management routines (malloc/calloc/free) based on Espressif SDK memory routines. Meantime the lib requires newlib to be built with -DMALLOC_PROVIDED flag to explude newlib's memory routine implementation from compilation process.

## How to use
If you have newlib compiled with -DMALLOC_PROVIDED you need to add this one to the list of libs to be linked to your binary. 

## Troubleshooting
If you try so and get linked messages like this:
```
/opt/lx106/bin/../lib/gcc/xtensa-lx106-elf/4.8.5/../../../../xtensa-lx106-elf/lib/libc.a(lib_a-stdio.o): In function `__sread':
/home/andrey/esp-open-sdk/crosstool-NG/.build/src/newlib-2.0.0/newlib/libc/stdio/stdio.c:48: undefined reference to `_read_r'
/opt/lx106/bin/../lib/gcc/xtensa-lx106-elf/4.8.5/../../../../xtensa-lx106-elf/lib/libc.a(lib_a-stdio.o): In function `__swrite':
/home/andrey/esp-open-sdk/crosstool-NG/.build/src/newlib-2.0.0/newlib/libc/stdio/stdio.c:89: undefined reference to `_lseek_r'
/home/andrey/esp-open-sdk/crosstool-NG/.build/src/newlib-2.0.0/newlib/libc/stdio/stdio.c:97: undefined reference to `_write_r'
/opt/lx106/bin/../lib/gcc/xtensa-lx106-elf/4.8.5/../../../../xtensa-lx106-elf/lib/libc.a(lib_a-stdio.o): In function `__sseek':
/home/andrey/esp-open-sdk/crosstool-NG/.build/src/newlib-2.0.0/newlib/libc/stdio/stdio.c:117: undefined reference to `_lseek_r'
```
Then you didn't put the lib into the list of libs to be linked.

If you get messages like "malloc is already defined in libc.a" then you're trying to link with newlib libary which was built without -DMALLOC_PROVIDED flag.

if you get messages like:
```
/opt/lx106/bin/../lib/gcc/xtensa-lx106-elf/4.8.5/../../../../xtensa-lx106-elf/lib/libc.a(lib_a-mallocr.o): In function `malloc_extend_top':
/home/andrey/esp-open-sdk/crosstool-NG/.build/src/newlib-2.0.0/newlib/libc/stdlib/mallocr.c:2165: undefined reference to `_sbrk_r'
/home/andrey/esp-open-sdk/crosstool-NG/.build/src/newlib-2.0.0/newlib/libc/stdlib/mallocr.c:2202: undefined reference to `_sbrk_r'
/opt/lx106/bin/../lib/gcc/xtensa-lx106-elf/4.8.5/../../../../xtensa-lx106-elf/lib/libc.a(lib_a-freer.o):(.literal+0x14): undefined reference to `_sbrk_r'
/opt/lx106/bin/../lib/gcc/xtensa-lx106-elf/4.8.5/../../../../xtensa-lx106-elf/lib/libc.a(lib_a-freer.o): In function `_malloc_trim_r':
/home/andrey/esp-open-sdk/crosstool-NG/.build/src/newlib-2.0.0/newlib/libc/stdlib/mallocr.c:3325: undefined reference to `_sbrk_r'
/home/andrey/esp-open-sdk/crosstool-NG/.build/src/newlib-2.0.0/newlib/libc/stdlib/mallocr.c:3332: undefined reference to `_sbrk_r'
```
then you're trying to link with newlib built with no -DMALLOC_PROVIDED flag and this lib is not in the list of libraries to be linked.


