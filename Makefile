BUILD_DIR=build
BLD=$(BUILD_DIR)/bootloader/bootloader.bin
OS=$(BUILD_DIR)/os/kernel.elf
DISK=$(BUILD_DIR)/disk.img

all: bootdisk

.PHONY: bootdisk bootloader os

bootloader:
	make -C bootloader

os:
	make -C os

bootdisk: bootloader os
	dd if=/dev/zero of=$(DISK) bs=512 count=2880
	dd conv=notrunc if=$(BLD) of=$(DISK) bs=512 count=1 seek=0
	dd conv=notrunc if=$(OS) of=$(DISK) bs=512 count=$$(($(shell stat --printf="%s" $(OS))/512)) seek=1

run: bootdisk
	qemu-system-i386 -machine q35 -hda $(DISK) -gdb tcp::26000 -S

clean:
	make -C bootloader clean
	make -C os clean

clean-all: clean
	rm $(DISK)

