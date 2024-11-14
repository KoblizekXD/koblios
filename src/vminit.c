#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <vminit.h>
#include <vmutil.h>
#include <string.h>

cpu_t *__cpu(mem_p memory)
{
	cpu_t* cpu = (cpu_t *) calloc(1, sizeof(cpu_t));
	return cpu;
}

mem_p __memory(size_t full_mem)
{
	mem_p mem = malloc(sizeof(memory_t));
    if (!mem) {
        return NULL;
    }

    memset(&mem->bios, 0, sizeof(bios_t));

    size_t extended_size = full_mem > MiB(1) ? full_mem - MiB(1) : 0;

    if (extended_size > 0) {
        mem->ext = malloc(extended_size);
        if (!mem->ext) {
            free(mem);
			return NULL;
        }
        memset(mem->ext, 0, extended_size);
    } else {
        mem->ext = NULL;
	}

    return mem;
}
