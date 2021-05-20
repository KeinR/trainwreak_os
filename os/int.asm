
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

common_int_handler: pushad mov eax, [esp + 4*8] ; Int #
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


; Descriptions of the interrupts is found in the Intel man v3, ch. 6.15
; That is where I yanked them from, which is why they sound very academic
; Some are paraphrased through...

nec_int_handler 0
nec_int_handler 1
nec_int_handler 2
nec_int_handler 3
nec_int_handler 4
nec_int_handler 5
nec_int_handler 6
nec_int_handler 7
; Error code is pushed, but it's always zero
ec_int_handler 8
nec_int_handler 9
; "The segment selector index for the segment descriptor that caused the violation"
; "If the EXT flag is set, it indicates that the exception was caused by an event...
; external to the running program"
ec_int_handler 10
; Just like 10, althrough slightly different, and also uses IDT flag
ec_int_handler 11
; If the exception was caused by a not-pressent stack segment or overflow of the new stack
; during inter-privilage level call, it contains the segment selector for the segment that caused 
; the exception. A normal violation will have an ec of 0
ec_int_handler 12
; The good ol' GPE
; If the fault condition was detected wile loading a segment descriptor, teh ec contains the segment selector or the
; IDT vector number of the segment descriptor. Otherwise, it's zero.
ec_int_handler 13
; The page fault handler, with some other stuff
ec_int_handler 14
nec_int_handler 15
nec_int_handler 16
; Error code is null, bit zero is possibly set (EST) if the #AC was 
; recognized during the delivery of an event other than a software interrupt
ec_int_handler 17
nec_int_handler 18
nec_int_handler 19
nec_int_handler 20
; Control protection exception handler
; ----
; For some bizzare reason, I don't see it mentioned in any tutorials,
; and it's omitted from the OS dev wiki page on exceptions.
; The only reason I know about it is that I was getting the itnerrupt list
; from the intel manual, and I decided to cross-refernce my list with other
; places.
; BeeOS appears to recognize it...
; So why(???)
; It's not like they made a post-humanous change to the x86 standard, right?
; Perhaps it's just not really used?
; Really weird stuff.
ec_int_handler 21

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






