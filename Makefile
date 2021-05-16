
bin=bootloader.bin kernel.bin
disk=disk.img

all: bootdisk

%.bin: src/%.asm
	nasm -f bin $< -o $@

bootdisk: $(bin)
	dd if=/dev/zero of=$(disk) bs=512 count=2880
	dd conv=notrunc if=bootloader.bin of=$(disk) bs=512 count=1 seek=0
	dd conv=notrunc if=kernel.bin of=$(disk) bs=512 count=1 seek=1

clean-tmp:
	rm -f $(bin)

clean: clean-tmp
	rm -f $(disk)
	

