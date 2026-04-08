bits 16
org 0x7C00

start:
    mov ax, 0x0013
    int 0x10

    mov ax, 0xA000
    mov es, ax
    xor di, di
    
main:
    mov byte [es:di], 4
    inc di
    call pause
    jmp main

pause:
    mov cx, 0xFFFF
.loop:
    loop .loop
    ret

times 510 - ($ - $$) db 0
dw 0xAA55