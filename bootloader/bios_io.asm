; -----------------------------------
; BIOS text I/O functions
; -----------------------------------
; 
; References:
; https://wiki.osdev.org/Text_Mode_Cursor
; https://wiki.osdev.org/Babystep2
; https://wiki.osdev.org/Text_mode
; http://www.osdever.net/bkerndev/Docs/printing.htm
; https://software.intel.com/content/dam/develop/external/us/en/documents-tps/325383-sdm-vol-2abcd.pdf
; https://www.phatcode.net/res/221/files/vbe20.pdf (Got me thinking about "text mode")
; 
; Note that we use cdecl
;


; Move cursor to screen loc and remember
; dl < x coord
; dh < y coord
bios_movc:
    mov ah, 0x02
    xor bh, bh
    int 10h
    ret

; Print char on screen at cursor
; al < char 
; bh < color mask (upper 4 bg, lower 4 fg)
; cx < repeat
; Note: Params are unmodified, except for cx
bios_putc:
    .loop:
    cmp cx, 0
    je .end

    mov ah, 0x0e
    int 10h

    dec cx
    jmp .loop
    .end:
    ret

; print a string
; ds:si < zero-term string
; Note: ds is unmodified
bios_print:
    mov ah, 0x0e

    .loop:
    lodsb
    cmp al, 0
    je .end
    mov bh, 0x0F ; Default to back on white
    int 10h
    jmp .loop
    .end:

    ret

; Restore cursor to 0, 0
bios_restc:
    xor dx, dx
    call bios_movc
    ret

; Clears the screen
bios_cls:
    call bios_discurs
    call bios_restc

    mov al, ' '
    xor bh, bh
    mov cx, 80*50
    call bios_putc

    call bios_restc
    call bios_encurs
    ret

; Enable the cursor
bios_encurs:
    mov ah, 0x01
    ; Flat boi
    mov ch, 11
    mov cl, 12
    int 10h
    ret

; Disable cursor
bios_discurs:
    mov ah, 0x01
    mov ch, 0x3f
    int 10h
    ret






