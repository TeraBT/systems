print_bios:
    mov bx, 0
.loop:
    lodsb
    cmp al, 0
    je .done
    call .print_char
    jmp .loop
.done:
    ret

.print_char:
    mov ah, 0eh
    int 0x10
    ret

; ------------------------------

enable_a20:
    in al, 0x92
    or al, 00000010b
    out 0x92, al
    ret

; ------------------------------

print_hex_byte:
    ; input: AL = byte to print
    push ax
    push bx

    mov bl, al

    ; high nibble
    mov al, bl
    shr al, 4
    call nibble_to_ascii
    mov [hex_buffer], al

    ; low nibble
    mov al, bl
    and al, 0x0F
    call nibble_to_ascii
    mov [hex_buffer + 1], al

    mov byte [hex_buffer + 2], 13
    mov byte [hex_buffer + 3], 10
    mov byte [hex_buffer + 4], 0

    mov si, hex_buffer
    call print_bios

    pop bx
    pop ax
    ret

nibble_to_ascii:
    cmp al, 9
    jbe .digit
    add al, 'a' - 10
    ret
.digit:
    add al, '0'
    ret

hex_buffer db '00', 13, 10, 0