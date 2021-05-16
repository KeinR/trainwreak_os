
mov si, yay
call print

hlt

%include "src/bios_io.asm"

yay db `Kernel booted!\r\n\0`

