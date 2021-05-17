BUILD_DIR=../build/bootloader

BT_SRC := bootloader.asm
BT_OBJ := $(patsubst %.asm, $(BUILD_DIR)/%.bin, $(BT_SRC))

all: $(BT_OBJ)

$(BUILD_DIR)/%.bin: %.asm
	nasm -f elf $< -F dwarf -g -o $@.o
	ld -m elf_i386 -T bootloader.lds $@.o -o $@.elf
	objcopy -O binary $@.elf $@


clean:
	rm $(BUILD_DIR)/*


