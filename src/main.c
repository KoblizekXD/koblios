#include <string.h>
#include <vmutil.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <vminit.h>
#include <errno.h>

#define ERROR(FORMAT, ...) fprintf(stderr, FORMAT, ##__VA_ARGS__); return EXIT_FAILURE;

int main(int argc, char **argv)
{
	size_t mem_size = MiB(1);
	if (argc == 1) {
		ERROR("Error: Missing drive argument\n");
	}
	
	FILE* f = fopen(argv[1], "r");

	if (!f) {
		ERROR("Error: Could not open %s for reading: %s\n", argv[1], strerror(errno));
	}

	memory_t memory = __memory(mem_size);
	cpu_t *cpu = __cpu(mem_size);

	if (fread(memory + 0x7C00, 1, 512, f) < 512) {
		printf("Warning: all 512 were not read.\n");
	}

	fclose(f);
	
	free(memory);
	free(cpu);

	return EXIT_SUCCESS;
}
