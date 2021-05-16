#!/usr/bin/bash

nasm -f bin src/bootloader.asm -o bootloader.bin
# nasm -f bin src/io.asm -o io.bin
dd if=/dev/zero of=disk.img bs=512 count=2880
dd conv=notrunc if=bootloader.bin of=disk.img bs=512
# rm -f bootloader.bin io.bin

