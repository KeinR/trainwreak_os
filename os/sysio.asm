
global inb
global outb
global iowait

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

; Delay for a little while, for waiting for I/O operations to complete
; when we don't have interrupts configured/enabled yet.
; The operation writes to a port that is only used during the
; Power On Self Test (POST) phase of the computer, when it's powering op,
; so it should be safe to use.
; Apparently the Linux kernel thinks it's safe as well (ref; osdev wiki).
; I would think to use the serial ports as they're only used for legacy devices,
; but I guess that's exactly why we *don't* use them for this kind of stuff.
iowait:
    xor al, al
    out 0x80, al
    ret

