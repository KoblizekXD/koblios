#include <assert.h>
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vminit.h>
#include <vmutil.h>
#include <string.h>
#include <capstone/capstone.h>
#include <insndef.h>

cpu_t *__cpu(mem_p memory)
{
	cpu_t* cpu = (cpu_t *) calloc(1, sizeof(cpu_t));
	cpu->ebp = 0x7BFF;
	cpu->esp = cpu->ebp;
	cpu->eflags = 0x00000002;
	return cpu;
}

mem_p __memory(size_t full_mem)
{
	mem_p mem = malloc(sizeof(memory_t));
    if (!mem) {
        return NULL;
    }
	
	memset(mem, 0, sizeof(memory_t));
    size_t extended_size = full_mem > MiB(1) ? full_mem - MiB(1) : 0;

    if (extended_size > 0) {
        mem->ext = malloc(extended_size);
        if (!mem->ext) {
            free(mem);
        } else memset(mem->ext, 0, extended_size);
    } else {
        mem->ext = NULL;
	}
    return mem;
}

void __mem_destroy(mem_p memory)
{
	if (memory == NULL) return;
	if (memory->ext != NULL)
		free(memory->ext);
	free(memory);
}

extern void init_disp(uint8_t* text_memory, uint8_t* video_memory);
extern void draw_callback();

void _insn_execute(cpu_t* cpu, mem_p memory, cs_insn* instructions, size_t count)
{
	if (UINT16_T((uint8_t*) memory + 0x7C00 + 510) != 0xAA55) {
		const char* text = "Error: Invalid boot-sector.";
		for (size_t i = 0; i < strlen(text); i++) {
			MEMSET(memory, 0xB8000 + (i * 2), text[i]);
		}
		memory->mb_bios[0] = 0x1;
	}
	for (size_t i = 0; i < count; i++) {
		if (memory->mb_bios[0]) break;
		cs_insn instruction = instructions[i];
		instruction_callback cb = match_callback(instruction);
		cpu->eip = instruction.address;
		if (cb != NULL)
			cb(cpu, memory, instruction, instruction.detail->x86.operands);
	}
}

/*
 * This function is responsible for:
 * - Default screen render job
 * - Load the boot sector and process its instructions
 */
void __emulate_begin(cpu_t *cpu, mem_p memory)
{
	uint8_t *base_exec_address = (uint8_t*) memory + 0x7C00;
	init_disp((uint8_t*) memory + 0xB8000, (uint8_t*) memory + 0xA0000);

	const char* text = "Simple BIOS Emulator by aa55h";
	for (size_t i = 0; i < strlen(text); i++) {
		MEMSET(memory, 0xB8000 + (i * 2), text[i]);
	}

	memory->mb_bios[0] = 0x0;
	csh handle;
	if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK)
		return;
	cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);
	cs_insn* instructions;
	size_t count = cs_disasm(handle, base_exec_address, 510, 0x7C00, 0, &instructions);	

	while (!WindowShouldClose())
	{
		_insn_execute(cpu, memory, instructions, count);
		draw_callback();
	}
	
	cs_free(instructions, count);
	cs_close(&handle);
	CloseWindow();
}
