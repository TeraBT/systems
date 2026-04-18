bits 32

global kernel_entry
extern kmain

kernel_entry:
    jmp short next
    kernel_sig: db 'HRTL', 0

next:
    cld
    mov ah, 0x04
    mov esi, kernel_sig
    mov edi, 0xb8000
    call .print_loop
    call kmain

.hang:
    cli
    hlt
    jmp .hang

.print_loop:
    lodsb
    test al, al
    jz .end
    mov [edi], ax
    add edi, 2
    jmp .print_loop
.end:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits