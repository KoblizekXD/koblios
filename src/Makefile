ASM := nasm
FORMAT := bin
OUTPUT := ../build/bootable.bin
INPUT := bootable.asm

.PHONY: all clean

all: $(OUTPUT)

$(OUTPUT): $(INPUT)
	$(ASM) -f $(FORMAT) -o $(OUTPUT) $(INPUT)

clean:
	rm -f $(OUTPUT)
