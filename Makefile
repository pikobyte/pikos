# ==============================================================================
# PikOS Makefile
# ==============================================================================
# Builds the boot-sector, the kernel and links them together into an binary
# file pikos.bin. The run rule uses qemu by default and the debug rule launches
# a remote gdb environment.
# ==============================================================================

CC = gcc
GDB = gdb
CFLAGS = -m32 -g -nostdlib -nostdinc -I ./include -O0 -Wall -Wpedantic -Werror \
		 -ansi

C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard common/*.h kernel/*.h drivers/*.h cpu/*.h)
OBJ = ${C_SOURCES:.c=.o}

pikos.bin: boot/pikos_bootsect.bin kernel.bin
	cat $^ > pikos.bin

kernel.bin: boot/pikos_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/pikos_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ 

run: pikos.bin
	qemu-system-x86_64 -fda pikos.bin

debug: pikos.bin kernel.elf
	qemu-system-x86_64 -s -fda pikos.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o pikos.bin *.elf
	rm -rf boot/*.bin boot/*.o kernel/*.o drivers/*.o cpu/*.o

.PHONY: clean