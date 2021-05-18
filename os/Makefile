BUILD_DIR=../build/os

CFLAGS+=-ffreestanding -nostdlib -gdwarf-4 -m32 -ggdb3

OS_ASRC := $(wildcard *.asm)
OS_CSRC := $(wildcard *.c)
OS_AOBJ := $(patsubst %.asm, $(BUILD_DIR)/%.asm.o, $(OS_ASRC))
OS_COBJ := $(patsubst %.c, $(BUILD_DIR)/%.c.o, $(OS_CSRC))
OS_KERNEL := $(BUILD_DIR)/kernel.elf

all: $(OS_KERNEL)

$(BUILD_DIR)/%.asm.o: %.asm
	nasm -f elf32 $< -o $@

$(BUILD_DIR)/%.c.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(OS_KERNEL): $(OS_COBJ) $(OS_AOBJ) os.lds
	ld -nmagic -m elf_i386 -Tos.lds $(OS_COBJ) $(OS_AOBJ) -o $@

clean:
	rm $(OS_COBJ)

