#!/usr/bin/bash

qemu-system-i386 -machine q35 -fda disk.img -gdb tcp::26000 -S

