; -----------------------
; Bootloader
; ----------------------
; 
; References:
; https://raw.githubusercontent.com/tuhdo/os01/master/Operating_Systems_From_0_to_1.pdf
; https://software.intel.com/content/dam/develop/external/us/en/documents-tps/253665-sdm-vol-1.pdf
; https://en.wikipedia.org/wiki/Master_boot_record
; https://www.nasm.us/xdoc/2.15.05/html/nasmdoc0.html

org 0x7c00
bits 16

start: jmp boot

msg db `Hellow World!\r\nMight want to pack a spare set of knives...\0`

boot:
    ; mov eax, 0xCAFE
    ; mov edx, 0xBABE
    xor ax, ax
    mov ds, ax
    cld

    call cls
    mov si, msg
    call print

    cli
    hlt

bios_print:
   lodsb
   or al, al  ;zero=end of str
   jz done    ;get out
   mov ah, 0x0E
   mov bh, 0
   int 0x10
   jmp bios_print
done:
   ret

%include "src/bios_io.asm"

times 510 - ($-$$) db 0
dw 0xAA55


