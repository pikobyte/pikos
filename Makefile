# ==============================================================================
# PikOS Makefile
# ==============================================================================
# Builds the boot-sector, the kernel and links them together into an binary
# file pikos.bin. The run rule uses qemu by default and the debug rule launches
# a remote gdb environment.
# ==============================================================================

CC = gcc
GDB = gdb
CFLAGS = -m32 -std=c2x -g -O0 -Wall -Wpedantic -Werror -nostdlib -nostdinc \
	     -nostartfiles -nodefaultlibs -fno-builtin -fno-stack-protector \
		 -fno-pie -ffreestanding

C_SOURCES = $(wildcard common/*.c kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard common/*.h kernel/*.h drivers/*.h cpu/*.h)
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

pikos.bin: boot/pikos_bootsect.bin kernel.bin
	cat $^ > pikos.bin

kernel.bin: boot/pikos_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/pikos_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ 

run: pikos.bin
	qemu-system-i386 -drive format=raw,file=pikos.bin,index=0,if=floppy

debug: pikos.bin kernel.elf
	qemu-system-i386 -s \
	-drive format=raw,file=pikos.bin,index=0,if=floppy &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o pikos.bin *.elf
	rm -rf boot/*.bin boot/*.o common/*.o kernel/*.o drivers/*.o cpu/*.o

.PHONY: clean