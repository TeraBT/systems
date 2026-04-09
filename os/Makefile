NASM = nasm

all: os.img

boot.bin: boot.asm bootloader_utils.asm
	$(NASM) -f bin boot.asm -o boot.bin

stage2.bin: stage2.asm bootloader_utils.asm
	$(NASM) -f bin stage2.asm -o stage2.bin

os.img: boot.bin stage2.bin
	cat boot.bin stage2.bin > os.img

clean:
	rm -f boot.bin stage2.bin os.img

.PHONY: all clean