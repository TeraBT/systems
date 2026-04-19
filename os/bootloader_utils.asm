print_bios:
    mov bx, 0
.loop:
    lodsb
    test al, al
    jz .done
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
    ; input: al = byte to print
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

; ------------------------------
;       Sleep utils
; ------------------------------

tick_count: dw 0 

register_timer_interrupt_handler:
    cli
    mov word [0x20], timer_interrupt_handler
    mov word [0x22], cs
    sti
    ret

timer_interrupt_handler:
    push ax
    inc dword [tick_count]
    mov al, 0x20
    out 0x20, al ; write EOI to master PIC
    pop ax
    iret

sleep:
    ; input: ax = time to sleep 
    add ax, [tick_count]
.wait:
    cmp [tick_count], ax
    jae .done
    sti
    hlt
    jmp .wait
.done:
    ret
