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

msg db `Hellow World!\r\nMight want to pack a spare set of knives...\r\n\0`
nloading db `Loading kernel....\r\n\0`
nbooting db `Booting kernel....\r\n\0`

boot:
    cli
    cld

    call cls
    mov si, nloading
    call print
    
    mov ax, 0x50

    mov es, ax
    xor bx, bx

    mov al, 2
    mov ch, 0
    mov cl, 2 
    mov dh, 0 
    mov dl, 0

    mov ah, 0x02
    int 0x13

    mov si, nbooting
    call print

    ; Configure kernel env
    ; mov ds, 0x50
    jmp 0x50:0x0

    hlt

%include "src/bios_io.asm"

times 510 - ($-$$) db 0
dw 0xAA55


