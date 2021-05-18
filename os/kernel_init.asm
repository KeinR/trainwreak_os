
extern kmain
global main

section .text 


bits 16
main:
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    ; I've seen it called this online
    ; so I trust it's good form
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

    ; NB: Kernel stack overwrites the bootloader!!!
    ; Should relocate tomorrow
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    mov ebp, esp

    ; xor ax, ax
    ; mov ds, ax
    ; mov eax, 0xb8000
    ; mov cx, 0xFF26
    ; mov [ds:eax], cx
    ; mov al, ds:[eax]
    ; mov dl, ds:[eax + 2]
    call kmain
    hlt

section .data

gdt_null dd 0x0
    dd 0x0
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
gdt_descriptor dw word gdt_descriptor - gdt_null
    dd dword gdt_null

section .bss

KERNEL_STACK_SIZE equ 0x10000

align 4
kernel_stack:
    resb KERNEL_STACK_SIZE




