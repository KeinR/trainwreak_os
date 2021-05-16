
mov eax, 0x69
add eax, 1
mov si, iqq
call cls
mov al, 'a'
mov bh, 0xF0
mov cx, 10
call putc

hlt

%include "src/bios_io.asm"

iqq db `Kernel loaded!\r\n\0`

