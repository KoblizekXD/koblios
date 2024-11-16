#ifndef INSNDEF_H
#define INSNDEF_H

/*
 * Welcome to the hell, I said.
 * Pure macro madness
 */

#include <capstone/capstone.h>
#include <capstone/x86.h>
#include <capstone/xcore.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <vmutil.h>

typedef void (*instruction_callback)(cpu_t*, mem_p, cs_insn, cs_x86_op*);

typedef struct _instruction {
	const char* name;
	size_t operand_count;
} instruction_t;

#define DEFINE_INSTRUCTION(NAME, EXPECTED_OPERANDS) \
	instruction_t insn_data_##NAME = { #NAME, EXPECTED_OPERANDS }; \
	void NAME##_callback(cpu_t *cpu, mem_p memory, cs_insn instruction, cs_x86_op *operands)

uint16_t value_of(cpu_t *cpu, mem_p memory, cs_x86_op op)
{
	if (op.type == X86_OP_IMM) {
		return op.imm;
	} else if (op.type == X86_OP_REG) {

	} else {

	}
}

DEFINE_INSTRUCTION(mov, 2) {
	
}

DEFINE_INSTRUCTION(hlt, 0) {
	memory->mb_bios[0] = 0x1;
	printf("Instruction execution paused.\n");
}

DEFINE_INSTRUCTION(push, 1) {
	
}

#define BEGIN_SWITCH(FIRST) if (strcmp(instruction.mnemonic, #FIRST) == 0 && instruction.detail->x86.op_count == insn_data_##FIRST.operand_count) return &FIRST##_callback;
#define OR(OTHER) else if (strcmp(instruction.mnemonic, #OTHER) == 0 && instruction.detail->x86.op_count == insn_data_##OTHER.operand_count) return &OTHER##_callback;

instruction_callback match_callback(cs_insn instruction)
{
	BEGIN_SWITCH(mov)
		OR(hlt)
	return NULL;
}

#endif
