NASM = nasm
CC = gcc
LD = ld
OBJCOPY = objcopy

CFLAGS = -m32 -ffreestanding -fno-pic -fno-pie -nostdlib -nostartfiles -nodefaultlibs -c
CERRORFLAGS = -Wall -Wextra -Wpedantic
LDFLAGS = -m elf_i386 -T linker.ld

all: os.img format

boot.bin: boot.asm bootloader_utils.asm
	$(NASM) -f bin boot.asm -o boot.bin

stage2.bin: stage2.asm bootloader_utils.asm
	$(NASM) -f bin stage2.asm -o stage2.bin

kernel_entry.o: kernel_entry.asm
	$(NASM) -f elf32 kernel_entry.asm -o kernel_entry.o

kutils.o: kutils.c kutils.h kstdint.h
	$(CC) $(CFLAGS) $(CERRORFLAGS) kutils.c -o kutils.o

kmain.o: kmain.c kutils.h kstdint.h
	$(CC) $(CFLAGS) $(CERRORFLAGS) kmain.c -o kmain.o

kernel.elf: kernel_entry.o kmain.o kutils.o linker.ld
	$(LD) $(LDFLAGS) kernel_entry.o kmain.o kutils.o -o kernel.elf

kernel.bin: kernel.elf
	$(OBJCOPY) -O binary kernel.elf kernel.bin

os.img: boot.bin stage2.bin kernel.bin
	cat boot.bin stage2.bin kernel.bin > os.img
	current_size=$$(stat -c%s os.img); \
	padded_size=$$(( ($$current_size + 511) / 512 * 512 )); \
	truncate -s $$padded_size os.img; \
	echo $$padded_size; \
	echo "Kernel sector count: $$(( ($$padded_size - 1024 ) / 512 ))"

clean:
	rm -f *.bin *.o *.elf *.img

format:
	clang-format -i *.c *.h

run: all
	qemu-system-i386 -drive format=raw,file=os.img

.PHONY: all clean format run