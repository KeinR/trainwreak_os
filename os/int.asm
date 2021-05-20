
bits 32
section .text

extern int_handler
global int_loadIDT

%macro nec_int_handler 1
global int_handler_%1
int_handler_%1:
    push    0 ; Push dummy error code to set up stack correctly
    push    %1
    jmp     common_int_handler
%endmacro

%macro ec_int_handler 1
global int_handler_%1
int_handler_%1:
    push    %1
    jmp     common_int_handler
%endmacro

common_int_handler:
    pushad
    mov eax, [esp + 4*8] ; Int #
    mov edx, [esp + 4*9] ; Error code
    push edx
    push eax ; First parameter
    ; TODO: The registers must be preserved,
    ; does this go for EFLAGS as well?
    call int_handler
    add esp, 8
    popad
    ; Pop interrupt number and error code
    add esp, 8

    iret

int_loadIDT:
    mov eax, [esp + 4]
    lidt [eax]
    sti
    ret

; PIC offset 0x20 = 32

nec_int_handler 32
nec_int_handler 33
nec_int_handler 34
nec_int_handler 35
nec_int_handler 36
nec_int_handler 37
nec_int_handler 38
nec_int_handler 39
nec_int_handler 40
nec_int_handler 41
nec_int_handler 42
nec_int_handler 43
nec_int_handler 44
nec_int_handler 45
nec_int_handler 46
nec_int_handler 47
nec_int_handler 48






