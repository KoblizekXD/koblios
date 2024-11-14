#ifndef VMINIT_H
#define VMINIT_H

#include <vmutil.h>
#include <stddef.h>

/* Defines standard functions used to initialize the emulator. */

cpu_t *__cpu(mem_p memory);
mem_p __memory(size_t size);
void  __mem_destroy(mem_p memory);

void __screen_init();

void __emulate_begin(cpu_t *cpu, mem_p memory);

#endif
