bits 16
org 0x7c00

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00
    sti

    mov [boot_drive], dl

    mov si, init_msg
    call print_bios

    call load_stage2_into_mem

.hang:
    cli
    hlt
    jmp .hang

load_stage2_into_mem:
    mov ah, 0x02
    mov al, 0x01
    mov ch, 0x00
    mov cl, 0x02
    mov dh, 0x00
    mov dl, [boot_drive]
    mov bx, 0x7e00
    int 0x13
    
    jc .load_error

    mov dl, [boot_drive]

    jmp 0x0000:0x7e00

.load_error:
    mov si, stage2_load_error_msg
    call print_bios
    ret

%include "bootloader_utils.asm"

boot_drive: db 0

init_msg:
    db 'Bootloader loaded.', 13, 10, 0

stage2_load_error_msg: db 'Error: Stage 2 not loaded into memory.', 13, 10, 0

times 510 - ($ - $$) db 0
dw 0xaa55