bits 16
org 0x7C00

start:
    mov ah, 0x0E
    mov al, 'H'
    int 0x10

loop:
    jmp loop

times 510 - ($ - $$) db 0
dw 0xAA55