mov r1 0x5
mov r2 -0x1
sti r1 r1
add r1 r1 r2
cmp r1 r0
beq 0x7
b 0x2
stop
^D
