
global kern_test_interrupts

section .text

kern_test_interrupts:
    ; int 1
    int 32
    ; jmp 0x0:fasf
    ; fasf:
    ; Generate GPE to test interrupts
    ; mov [40], dword 94
    ret


