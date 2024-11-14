#ifndef VMINIT_H
#define VMINIT_H

#include <vmutil.h>
#include <stddef.h>

/* Defines standard functions used to initialize the emulator. */

cpu_t *__cpu(mem_p memory);
mem_p __memory(size_t size);

void __screen_init();

#endif
