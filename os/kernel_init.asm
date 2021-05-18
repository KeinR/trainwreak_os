
; extern kmain
global main

section .text 


bits 16
main:
    cli
    xor ax, ax
    mov ds, ax
    xor eax, eax
    mov ebp, eax
    mov esp, eax

    ; mov eax, gdt
    ; mov [gdt_descr_adr], eax
    
    ; lgdt [gdt_descr]
    lgdt [gdt_descriptor]

    ; jmp 0x08 : foobar - 0x80
    ; foobar:

    ; mov eax, cr0
    ; or eax, 0x1 
    ; mov cr0, eax
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    cli

    jmp 0x08:flush_pipeline

bits 32
flush_pipeline:

    mov eax, 0xCAFEBABE

    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; mov esp, kernel_stack + KERNEL_STACK_SIZE
    ; mov ebp, esp

    xor ax, ax
    mov ds, ax
    mov eax, 0xb8000
    mov cx, 0xFF26
    mov [ds:eax], cx
    ; mov al, ds:[eax]
    ; mov dl, ds:[eax + 2]
    hlt
    ; call kmain

section .data

gdt_descr dw (8*3-1)
gdt_descr_adr db 0

; Null, code, data
gdt align 8, db 0, 0,         0,         0, 0, 0, 0,    0
    align 8, db 0, 01001111b, 10011110b, 0, 0, 0, 0xff, 0xff
    align 8, db 0, 01001111b, 10010010b, 0, 0, 0, 0xff, 0xff

gdt_null db 0x0
    db 0x0
gdt_code dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0
gdt_data dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0
gdt_descriptor dw dword gdt_descriptor - gdt_null
    db word gdt_null

section .bss

KERNEL_STACK_SIZE equ 0x1000

align 4
kernel_stack:
    resb KERNEL_STACK_SIZE




