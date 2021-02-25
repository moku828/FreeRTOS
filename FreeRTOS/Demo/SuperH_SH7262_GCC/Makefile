#/*
# * FreeRTOS Kernel V10.3.0
# * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
# *
# * Permission is hereby granted, free of charge, to any person obtaining a copy of
# * this software and associated documentation files (the "Software"), to deal in
# * the Software without restriction, including without limitation the rights to
# * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# * the Software, and to permit persons to whom the Software is furnished to do so,
# * subject to the following conditions:
# *
# * The above copyright notice and this permission notice shall be included in all
# * copies or substantial portions of the Software.
# *
# * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
# *
# * http://www.FreeRTOS.org
# * http://aws.amazon.com/freertos
# *
# * 1 tab == 4 spaces!
# */

CC=sh-elf-gcc
LD=sh-elf-ld
OBJCOPY=sh-elf-objcopy
ARCH=sh-elf-ar
DEBUG=-gdwarf-2 -gstrict-dwarf
OPTIM=-O0
LDSCRIPT=sh7262_large.ld

ASMFLAGS=-Wa,-gstabs
CFLAGS=-I./RTOSDemo -I../../Source/portable/GCC/SH2A_FPU -I../../Source/include \
		-I../Common/include $(DEBUG) $(OPTIM) -ffreestanding

#
# Source files
#
ASM_SRC = \
../../Source/portable/GCC/SH2A_FPU/portasm.s \
RTOSDemo/asmfunc.s \
RTOSDemo/regtest.s
C_SRC = \
../Common/Minimal/BlockQ.c \
../Common/Minimal/GenQTest.c \
../Common/Minimal/PollQ.c \
../Common/Minimal/QPeek.c \
../Common/Minimal/blocktim.c \
../Common/Minimal/death.c \
../Common/Minimal/flash.c \
../Common/Minimal/integer.c \
../Common/Minimal/recmutex.c \
../Common/Minimal/semtest.c \
RTOSDemo/ParTest/ParTest.c \
RTOSDemo/flop.c \
RTOSDemo/main.c \
RTOSDemo/printf-stdarg.c \
../../Source/list.c \
../../Source/portable/MemMang/heap_2.c \
../../Source/portable/GCC/SH2A_FPU/port.c \
../../Source/queue.c \
../../Source/tasks.c

#
# Define all object files.
#
ASM_OBJ = $(ASM_SRC:.s=.o)
C_OBJ = $(C_SRC:.c=.o)

rtosdemo.hex : rtosdemo.elf
	$(OBJCOPY) rtosdemo.elf -O ihex rtosdemo.hex

rtosdemo.elf : $(C_OBJ) $(ASM_OBJ) Makefile
	$(LD) -T $(LDSCRIPT) -o $@ $(C_OBJ) $(ASM_OBJ) -L /usr/local/sh-elf/lib/m2a -lc -L /usr/local/lib/gcc/sh-elf/10.2.0/m2a -lgcc -L /usr/local/sh-elf/lib/m2a -lm

$(ASM_OBJ) : %.o : %.s $(LDSCRIPT) Makefile
	$(CC) -c $(ASMFLAGS) $< -o $@

$(C_OBJ) : %.o : %.c $(LDSCRIPT) Makefile
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	touch Makefile
	rm $(ASM_OBJ)
	rm $(C_OBJ)
	rm rtosdemo.hex rtosdemo.elf
