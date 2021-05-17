BUILD_DIR=../build/os

CFLAGS+=-ffreestanding -nostdlib -gdwarf-4 -m32 -ggdb3

OS_ASRC := $(wildcard *.asm)
OS_CSRC := $(wildcard *.c)
OS_AOBJ := $(patsubst %.asm, $(BUILD_DIR)/%.o, $(OS_ASRC))
OS_COBJ := $(patsubst %.c, $(BUILD_DIR)/%.o, $(OS_CSRC))
OS_KERNEL := $(BUILD_DIR)/kernel.elf

all: $(OS_KERNEL)

$(BUILD_DIR)/%.bin: %.asm
	nasm -f bin $< -o $@

$(BUILD_DIR)/%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(OS_KERNEL): $(OS_COBJ) os.lds
	ld -nmagic -m elf_i386 -Tos.lds $(OS_COBJ) -o $@

clean:
	rm $(OS_COBJ)

