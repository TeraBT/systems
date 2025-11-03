BITS 64
default rel

extern printf
global main

section .data
num dq 4
format db "%d", 10, 0

section .text

main:
    mov bl, 0
start:

    mov rdi, format
    mov rsi, [num]
    xor eax, eax
    call printf
    inc byte [num]
    inc bl
    cmp bl, 40
    je end
    jmp start
end:
    xor eax, eax
    ret