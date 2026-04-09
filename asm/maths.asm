; ADDITION
mov al, 0x7F ; +127 (max signed 8 bit value)
add al, 1    ; 0x80 -128 ; OF = 1 (signed overflow)
             ; SF 0 1, ZF = 0, CF = 0
             ; 1000000b

mov rbx, 5
add rbx, 3
; rbx = 8

add qword[memory_label], rbx

memory_label: dq 0

; SUBTRACTION
mov rax, 0
sub rax, 1 ; CF=1(borrow, OF=1(signed overflow), rbx=-1

mov rbx, 10
sub rbx, 3 ; rbx=7

; MULTIPLICATION
; 64-BIT UNSIGNED MULTIPLICATION
mov rax, 5000
mov rbx, 10
mul rbx ; rdx:rax=rax*rbx=50000

; 64-bit unsigned multiplicaiton
; where we don't fit

mov rax, 0xFFFFFFFFFFFFFFFF
mov rbx, 2
mul rbx ; result=0x1FFFFFFFFFFFFFFFE
; rdx=0x01, rax=FFFFFFFFFFFFFFFE

; lower register multiplication
mov al, 25
mov bl, 10
mul bl; AX=250, CF=0, OF=0, AH=0

; overflow the lower half
mov al, 200
mov bl, 200
mul bl ; AX=40000, CF=1, OF=1

; signed multiplication
mov al, -5 ; 0xFB (251 d)
mov bl, 10 ; 0x0A
imul bl    ; AX = -50 -> 0xFFCE (65,486)

; signed multiplication with overflow
mov al, 100 ; 0x64
ov bl, 100 ; 0x64
imul bl; AX = (AL * BL = 10000 -> 0x2710)
; CF=1, OF=1

; two operand multiplication
mov rdx, 4
imul rdx, rsi ; rdx=rdx*rsi
; jo .overflow

; unsigned division
mov ax, 250 ; dividend in AX
mov bl, 10  ; divisor
div bl      ; AL=25(result), AH=0(reminder)

; reminder example
mov ax, 250
mov bl, 32
div bl  ; 250 / 32 = 7.8125 (floored => 7)
        ; AL=7, AH=26 (250 % 32 = 26)

; signed division
mox rax, 1000000000
xor rdx, rdx
mov rbx, 3
div rbx     ; RAX=3333333333 (10 mio / 3), RDX=1 (10 mio % 3 = 1)

; signed vidision
mov ax, -100
mov bl, 7
idiv bl ; AL=-14 (0xF2), AH=-2 (0xFE)