bits 16
org 0x7c00

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    mov [boot_drive], dl

    mov si, initial_message
    call print_bios

    call load_stage2

.hang:
    cli
    hlt
    jmp .hang

load_stage2:
    mov ah, 0x02
    mov al, 0x01
    mov ch, 0x00
    mov cl, 0x02
    mov dh, 0x00
    mov dl, [boot_drive]
    mov bx, 0x7E00
    int 0x13
    
    jc .handle_error

    jmp 0x0000:0x7E00

.handle_error:
    mov si, error_message
    call print_bios
    ret

%include "bootloader_utils.asm"

boot_drive: db 0

initial_message:
    db 'Bootloader loaded. Loading stage 2...', 13, 10, 0

error_message: db 'Error occurred.', 13, 10, 0

times 510 - ($ - $$) db 0
dw 0xaa55