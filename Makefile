CC = gcc
CFLAGS = -O3 -I ./src -Wall -Wextra -Wno-unused
LINKFLAGS = -lcapstone -lraylib
SRC_DIR = src/
SRC = $(shell find $(SRC_DIR) -name '*.c')
BUILD = build
OBJ = $(SRC:%.c=$(BUILD)/%.o)
OUTPUT = $(BUILD)/vm
TEST_BINARY = test/disk.bin

.PHONY: all clean

all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	$(CC) $(LINKFLAGS) -o $@ $^

$(BUILD)/%.o: %.c | $(BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
	mkdir -p $(BUILD)

run: $(OUTPUT)
	./$(OUTPUT) $(TEST_BINARY)
