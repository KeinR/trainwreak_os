
global inb
global outb

section .text

; Read byte from port
; char inb(short port)
inb:
    mov dx, [esp + 4]
    in al, dx
    ret

; Write byte to port
; void outb(short port, char byte)
outb:
    mov dx, [esp + 4]
    mov al, [esp + 8]
    out dx, al
    ret


