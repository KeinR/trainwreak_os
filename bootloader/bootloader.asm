; -----------------------
; Bootloader
; ----------------------
; 
; References:
; https://raw.githubusercontent.com/tuhdo/os01/master/Operating_Systems_From_0_to_1.pdf
; https://software.intel.com/content/dam/develop/external/us/en/documents-tps/253665-sdm-vol-1.pdf
; https://en.wikipedia.org/wiki/Master_boot_record
; https://www.nasm.us/xdoc/2.15.05/html/nasmdoc0.html

bits 16

start: jmp boot

nloading db `Loading kernel....\r\n\0`
nbooting db `Booting kernel....\r\n\0`

; smol stack
; Grows backwards, so bootloader safe (?)
; BL_STACK_SIZE equ 0xa0

boot:
    cli
    cld

    ; Told linker to set offset to 0x7c00,
    ; so segments offsets should be zero
    xor ax, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ds, ax
    jmp 0x0:ccs
    ccs:

    mov sp, 0x7c00
    mov bp, sp

    call bios_cls
    mov si, nloading
    call bios_print

    ; Read kernel from floppy

    mov ax, 0x50

    mov es, ax
    xor bx, bx

    mov al, 4 ; Sectors to read
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0

    mov ah, 0x02
    int 0x13

    mov si, nbooting
    call bios_print

    ; Configure kernel segments and transfer execution
    ; to where the code was loaded
    ; mov ax, 0x50
    ; mov es, ax
    ; mov fs, ax
    ; mov gs, ax
    ; mov ss, ax
    ; mov ds, ax
    xor ax, ax
    mov es, ax
    jmp [0x500 + 0x18]

    hlt

%include "bios_io.asm"

times 510 - ($-$$) db 0
dw 0xAA55


