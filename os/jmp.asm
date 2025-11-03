BITS 64
default rel

jmp 0x1000
jmp _routine
jmp rax
jmp qword [_pointer]
jmp $

_pointer: dq 0xffffffff
_routine: