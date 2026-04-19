%ifndef KERNEL_SECTOR_COUNT
%define KERNEL_SECTOR_COUNT 0x0000
%endif

bits 16
org 0x7e00

start2:
    cli
    xor ax, ax
    mov ds, ax

    mov [boot_drive], dl

    mov si, stage2_init_msg
    call print_bios

    call load_kernel_into_mem
   
    call register_timer_interrupt_handler
    mov ax, 16
    sti
    call sleep
    cli

    call enable_a20
 
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:protected_mode_entry

load_kernel_into_mem:
    mov si, dap
    mov ah, 0x42
    mov dl, [boot_drive]
    int 0x13
    jc .kernel_load_error
 
    mov ax, 0x1000
    mov es, ax
    mov bx, 0x0000
    cmp dword es:[bx + 2], 'HRTL'
    jne .kernel_bad_error

    mov si, kernel_good_msg
    call print_bios
    
    ret

.kernel_load_error:
    mov si, kernel_load_error_msg
    call print_bios
    jmp .hang

.kernel_bad_error:
    mov si, kernel_bad_msg
    call print_bios
    jmp .hang

.hang:
    cli
    hlt
    jmp .hang

boot_drive: db 0

kernel_load_error_msg: db 'Error: Kernel not loaded into memory.', 13, 10, 0
kernel_load_succ_msg: db 'Kernel loaded into memory.', 13, 10, 0

kernel_bad_msg: db 'Error: Kernel bad', 13, 10, 0
kernel_good_msg: db 'Kernel good.', 13, 10, 0

stage2_init_msg:
    db 'Stage 2 reached.', 13, 10, 0

%include "bootloader_utils.asm"

dap:
    db 0x10
    db 0x00
    dw KERNEL_SECTOR_COUNT
    dw 0x0000
    dw 0x1000
    dq 0x0000000000000002

; ------------------------------
; Protected Mode Setup
; ------------------------------

gdt_start:
    dq 0x0000000000000000
    dq 0x00cf9a000000ffff
    dq 0x00cf92000000ffff
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

bits 32
protected_mode_entry:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000

    jmp dword 0x08:0x10000

times 512 - ($ - $$) db 0