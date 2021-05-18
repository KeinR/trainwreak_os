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
ndiskfail db `Error: failed to read kernel!\r\n\0`

boot:
    cli
    cld

    ; Told linker to set offset to 0x7c00,
    ; so segments offsets should be zero
    xor ax, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ; mov ss, ax
    mov ds, ax
    jmp 0x0:ccs
    ccs:

    ; More than enough for BIOS
    mov sp, 0x100
    mov bp, sp
    mov ax, 0x7c00 - 0x100
    mov ss, ax

    call bios_cls
    mov si, nloading
    call bios_print

    ; Read kernel from disk

    mov si, 2 ; Read attempts

    mov al, 4 ; 512-byte sectors to read
    mov dl, 0x80 ; Drive number, starts at 0x80 for god knows why
    mov ch, 0 ; Cylander number
    mov dh, 0 ; Head number
    mov cl, 2 ; Starting sector number, counting from 1 (1 was bootloader)
    mov bx, 0x500 ; Buffer address
.read:
    mov ah, 2 ; Read sectors
    int 13h
    jnc .good
    dec si 
    jc .fail ; Interesting hack, when si < 0 the CF flag is set
    ; Failed to read disk
    ; Reset disk and try again
    xor ah, ah
    int 13
    jnc .read ; Only try again if reset was successful
.fail:
    mov si, ndiskfail
    call bios_print
    hlt
.good:

    mov si, nbooting
    call bios_print

    ; Zero segments and transfer execution to kernel
    xor ax, ax
    mov es, ax
    jmp [0x500 + 0x18]

    hlt ; Not actually needed

%include "bios_io.asm"

times 510 - ($-$$) db 0
dw 0xAA55


