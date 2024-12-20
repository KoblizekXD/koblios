#ifndef VMUTIL_H
#define VMUTIL_H

#include <stdint.h>

#define KiB(SIZE) (1024 * SIZE)
#define MiB(SIZE) (1024 * 1024 * SIZE)

#define X_REG(REGISTER) ((REGISTER) & 0xFFFF)
#define L_REG(REGISTER) ((REGISTER) & 0xFF)
#define H_REG(REGISTER) ((REGISTER >> 8) & 0xFF)

#define UINT16_T(ADDRESS) ((uint16_t)((*(ADDRESS)) | ((*(ADDRESS + 1)) << 8)))

#define MEMSET(MEMORY, ADDRESS, VALUE) ((uint8_t*) MEMORY)[ADDRESS] = VALUE

typedef uint32_t _x86_reg;

typedef struct _cpu {
	_x86_reg eax;
	_x86_reg ebx;
	_x86_reg ecx;
	_x86_reg edx;
	_x86_reg esi;
	_x86_reg edi;
	_x86_reg esp;
	_x86_reg ebp;

	_x86_reg eip;
	_x86_reg eflags;

	_x86_reg cr0;
	_x86_reg cr4;
} cpu_t;

// Sets the lower 16 bits of the given register(e.g. sets AX of EAX register)
inline void set_xreg(_x86_reg* reg, uint16_t value) {
    *reg = (*reg & 0xFFFF0000) | value;
}
// Sets the lowest 8 bits of the given register(e.g. sets AL of EAX register)
inline void set_lreg(_x86_reg* reg, uint8_t value) {
	*reg = (*reg & 0xFFFFFF00) | value;
}
// Sets the 2nd lowest 8 bits of the given register(e.g. sets AH of EAX register)
inline void set_hreg(_x86_reg* reg, uint8_t value) {
	*reg = (*reg & 0xFFFF00FF) | (value << 8);
}

typedef struct memory {
	uint8_t ivt[KiB(1)];
	uint8_t bda[256];
	uint8_t conventional[30464];
	uint8_t bootsector[512];
	uint8_t conventional_2[492032];
	uint8_t ebda[KiB(128)];
	uint8_t video[KiB(128)];
	uint8_t video_bios[KiB(32)];
	uint8_t bios_expansion[KiB(160)];
	uint8_t mb_bios[KiB(64)];
	uint8_t *ext;
} __attribute__((packed)) memory_t;

typedef memory_t *mem_p;

#endif
