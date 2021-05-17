

ENTRY(main);
PHDRS
{
headers PT_PHDR FILEHDR PHDRS;
code PT_LOAD;
}
SECTIONS
{
.text 0x500: { *(.text) } :code
.data : { *(.data) }
.bss : { *(.bss) }
/DISCARD/ : { *(.eh_frame) }
}



