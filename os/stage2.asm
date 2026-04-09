bits 16
org 0x7e00

start2:
    mov ax, 0x0000
    mov ds, ax

    mov si, stage2_message
    call print_bios

    call load_kernel

load_kernel:
    ; kernel entry
.hang:
    cli
    hlt
    jmp .hang

%include "bootloader_utils.asm"

stage2_message:
    db 'Stage 2 of bootloader loaded. Loading kernel...', 13, 10, 0

times 512 - ($ - $$) db 0