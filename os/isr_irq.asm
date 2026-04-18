bits 32

extern common_interrupt_handler

%macro ISR 3
global isr%1_entry
isr%1_entry:
    push dword %3
    push dword 0
    push dword %1
    jmp %2
%endmacro

%macro ISRE 3
global isr%1_entry
isr%1_entry:
    push dword %3
    push dword %1
    push dword %3
    jmp %2
%endmacro

%macro IRQ 4
global irq%1_entry
irq%1_entry:
    push dword %3
    push dword 0
    push dword %2
    jmp %3
%endmacro

global syscall_entry
syscall_entry:
    push dword 0x80
    jmp common_entry

common_entry:
    pusha

    lea eax, [esp + 32]
    push eax
    call common_interrupt_handler
    add esp, 4

    popa
    add esp, 12
    
    iret

ISR 0, common_entry, common_interrupt_handler
ISR 1, common_entry, common_interrupt_handler
ISR 2, common_entry, common_interrupt_handler
ISR 3, common_entry, common_interrupt_handler
ISR 4, common_entry, common_interrupt_handler
ISR 5, common_entry, common_interrupt_handler
ISR 6, common_entry, common_interrupt_handler
ISR 7, common_entry, common_interrupt_handler
ISRE 8, common_entry, common_interrupt_handler
ISR 9, common_entry, common_interrupt_handler
ISRE 10, common_entry, common_interrupt_handler
ISRE 11, common_entry, common_interrupt_handler
ISRE 12, common_entry, common_interrupt_handler
ISRE 13, common_entry, common_interrupt_handler
ISRE 14, common_entry, common_interrupt_handler
ISR 15, common_entry, common_interrupt_handler
ISR 16, common_entry, common_interrupt_handler
ISRE 17, common_entry, common_interrupt_handler
ISR 18, common_entry, common_interrupt_handler
ISR 19, common_entry, common_interrupt_handler
ISR 20, common_entry, common_interrupt_handler
ISR 21, common_entry, common_interrupt_handler
ISR 22, common_entry, common_interrupt_handler
ISR 23, common_entry, common_interrupt_handler
ISR 24, common_entry, common_interrupt_handler
ISR 25, common_entry, common_interrupt_handler
ISR 26, common_entry, common_interrupt_handler
ISR 27, common_entry, common_interrupt_handler
ISR 28, common_entry, common_interrupt_handler
ISR 29, common_entry, common_interrupt_handler
ISRE 30, common_entry, common_interrupt_handler
ISR 31, common_entry, common_interrupt_handler

IRQ 0, 32, common_entry, common_interrupt_handler
IRQ 1, 33, common_entry, common_interrupt_handler
IRQ 2, 34, common_entry, common_interrupt_handler
IRQ 3, 35, common_entry, common_interrupt_handler
IRQ 4, 36, common_entry, common_interrupt_handler
IRQ 5, 37, common_entry, common_interrupt_handler
IRQ 6, 38, common_entry, common_interrupt_handler
IRQ 7, 39, common_entry, common_interrupt_handler
IRQ 8, 40, common_entry, common_interrupt_handler
IRQ 9, 41, common_entry, common_interrupt_handler
IRQ 10, 42, common_entry, common_interrupt_handler
IRQ 11, 43, common_entry, common_interrupt_handler
IRQ 12, 44, common_entry, common_interrupt_handler
IRQ 13, 45, common_entry, common_interrupt_handler
IRQ 14, 46, common_entry, common_interrupt_handler
IRQ 15, 47, common_entry, common_interrupt_handler



section .note.GNU-stack noalloc noexec nowrite progbits
