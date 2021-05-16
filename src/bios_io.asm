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


; Move cursor to screen loc and remember
; dl < x coord
; dh < y coord
movc:
    push ax
    push bx
    
    mov ah, 0x02
    xor bh, bh
    int 10h

    pop bx
    pop ax
    ret

; Print char on screen at cursor
; al < char 
; bh < color mask (upper 4 bg, lower 4 fg)
; cx < repeat
; Note: Params are unmodified, except for cx
putc:
    push ax

    .loop:
    cmp cx, 0
    je .end

    mov ah, 0x0e
    int 10h

    dec cx
    jmp .loop
    .end:

    pop ax
    ret

; print a string
; ds:si < zero-term string
; Note: ds is unmodified
print:
    push ax
    mov ah, 0x0e

    .loop:
    lodsb
    cmp al, 0
    je .end
    mov bh, 0x0F ; Default to back on white
    int 10h
    jmp .loop
    .end:

    pop ax
    ret

; Restore cursor to 0, 0
restc:
    push dx
    xor dx, dx
    call movc
    pop dx
    ret

; Clears the screen
cls:
    call discurs
    call restc

    push ax
    push bx
    push cx

    mov al, ' '
    xor bh, bh
    mov cx, 80*50
    call putc

    pop cx
    pop bx
    pop ax

    call restc
    call encurs
    ret

; Enable the cursor
encurs:
    push ax
    push cx

    mov ah, 0x01
    ; Flat boi
    mov ch, 11
    mov cl, 12
    int 10h

    pop cx
    pop ax
    ret

; Disable cursor
discurs:
    push ax
    push cx

    mov ah, 0x01
    mov ch, 0x3f
    int 10h

    pop cx
    pop ax
    ret






