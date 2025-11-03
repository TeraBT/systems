BITS 64
default rel

section .data
msg: db "Hello World", 0x0A

section .text
global _start

_start:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel msg]
    mov rdx, 12
    syscall

    mov rax, 60
    xor rdi, rdi
    syscall