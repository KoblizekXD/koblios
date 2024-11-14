CC = gcc
CFLAGS = -O3 -g -I ./src -Wall -Wextra -Wno-unused
LINKFLAGS = -lcapstone -lraylib
SRC_DIR = src/
SRC = $(shell find $(SRC_DIR) -name '*.c')
BUILD = build
OBJ = $(SRC:%.c=$(BUILD)/%.o)
OUTPUT = $(BUILD)/vm
TEST_BINARY = build/bootable.bin

.PHONY: all clean

run: $(OUTPUT)
	./$(OUTPUT) $(TEST_BINARY)


all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	$(CC) $(LINKFLAGS) -o $@ $^
	make -C src/

$(BUILD)/%.o: %.c | $(BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
	mkdir -p $(BUILD)
