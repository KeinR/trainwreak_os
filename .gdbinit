define hook-stop
    printf "[%4x:%4x]", $cs, $eip
    x/i $eip
end

set disassembly-flavor intel

# set architecture i386
set architecture i8086
symbol-file build/bootloader/bootloader.bin.elf
symbol-file build/os/kernel.elf
target remote localhost:26000

b kmain
b main
b *0x7c00
c

