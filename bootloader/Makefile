BUILD_DIR=../build/bootloader

BT_SRC := bootloader.asm
BT_OBJ := $(patsubst %.asm, $(BUILD_DIR)/%.bin, $(BT_SRC))

all: $(BT_OBJ)

$(BUILD_DIR)/%.bin: %.asm
	nasm -f bin $< -o $@

clean:
	rm $(BUILD_DIR)/*


