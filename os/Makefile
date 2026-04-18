NASM = nasm
CC = gcc
LD = ld
OBJCOPY = objcopy

CFLAGS = -m32 -ffreestanding -fno-pic -fno-pie -nostdlib -nostartfiles -nodefaultlibs -c
CERRORFLAGS = -Wall -Wextra -Wpedantic
LDFLAGS = -m elf_i386 -T linker.ld

KERNEL_SECTOR_COUNT = $$(( ($$(stat -c%s kernel.bin) + 511) / 512 ))

all: os.img format

boot.bin: boot.asm bootloader_utils.asm
	@$(NASM) -f bin boot.asm -o boot.bin

stage2.bin: stage2.asm bootloader_utils.asm kernel.bin
	@$(NASM) -f bin \
	-DKERNEL_SECTOR_COUNT=$(KERNEL_SECTOR_COUNT) \
	stage2.asm -o stage2.bin

kernel_entry.o: kernel_entry.asm
	@$(NASM) -f elf32 kernel_entry.asm -o kernel_entry.o

isr_irq.o: isr_irq.asm
	@$(NASM) -f elf32 isr_irq.asm -o isr_irq.o

idt.o: idt.c idt.h kstdint.h 
	@$(CC) $(CFLAGS) $(CERRORFLAGS) idt.c -o idt.o

kutils.o: kutils.c kutils.h kstddef.h kstdint.h 
	@$(CC) $(CFLAGS) $(CERRORFLAGS) kutils.c -o kutils.o

kmain.o: kmain.c  kstddef.h kstdint.h kutils.h idt.h
	@$(CC) $(CFLAGS) $(CERRORFLAGS) kmain.c -o kmain.o

kernel.elf: kernel_entry.o isr_irq.o kmain.o kutils.o idt.o linker.ld
	@$(LD) $(LDFLAGS) kernel_entry.o isr_irq.o kmain.o kutils.o idt.o -o kernel.elf

kernel.bin: kernel.elf
	@$(OBJCOPY) -O binary kernel.elf kernel.bin

os.img: boot.bin stage2.bin kernel.bin
	@cat boot.bin stage2.bin kernel.bin > os.img
	@current_size=$$(stat -c%s os.img); \
	padded_size=$$(( ($$current_size + 511) / 512 * 512 )); \
	truncate -s $$padded_size os.img; \
	echo "Unpadded image size: $$current_size"; \
	echo "Padded image size: $$padded_size"; \
	echo "Kernel sector count: $(KERNEL_SECTOR_COUNT)"; \
	echo "Total sector count: $$(( $$padded_size / 512 ))"

clean:
	rm -f *.bin *.o *.elf *.img

format:
	@clang-format -i *.c *.h

run: all
	qemu-system-i386 -drive format=raw,file=os.img

.PHONY: all clean format run