
bits 32

SCRBUF equ 0xb8000

global tty_putc

; void tty_putc(short c, int index)
tty_putc:
    push ebp
    mov ebp, esp
    push bx
    push ds

    xor bx, bx
    mov ds, bx
    mov bx, [ebp + 0x8]
    mov ecx, [ebp + 0xc]
    mov [ds:SCRBUF + ecx], bx

    pop ds
    pop bx
    pop ebp
    ret



