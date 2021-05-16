BUILD_DIR=../build/os

OS_SRC := $(wildcard *.asm)
OS_OBJ := $(patsubst %.asm, $(BUILD_DIR)/%.bin, $(OS_SRC))

all: $(OS_OBJ)

$(BUILD_DIR)/%.bin: %.asm
	nasm -f bin $< -o $@

clean:
	rm $(BUILD_DIR)/*

