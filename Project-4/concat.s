main:
    ;mov r3, &"hello"
    mov r2, #5
    ;mov r1, &"goodbye"
    mov r0, #7
    add r4, r2, r0
    mov r5, #1
    add r4, r4, r5
    bl allocate
allocate:
    