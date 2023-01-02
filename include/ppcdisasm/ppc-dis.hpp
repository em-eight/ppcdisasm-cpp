
#pragma once

extern "C" {
#include "opcode/ppc.h"
}
#include <iostream>
#include <string>
#include <functional>

typedef std::function<std::string(int32_t)> SymbolGetter;

// same for gekko and broadway
extern const ppc_cpu_t ppc_750cl_dialect;

void disassemble_init_powerpc ();
/* Find a match for INSN in the opcode table, given machine DIALECT.  */
const struct powerpc_opcode* lookup_powerpc (uint64_t insn, ppc_cpu_t dialect);
/* Extract the operand value from the PowerPC or POWER instruction.  */
int64_t operand_value_powerpc (const struct powerpc_operand *operand, uint64_t insn, ppc_cpu_t dialect);
inline int64_t operand_value_powerpc (uint32_t opindex, uint64_t insn, ppc_cpu_t dialect) 
    { return operand_value_powerpc(&powerpc_operands[opindex], insn, dialect); }

int cout_insn_powerpc(uint64_t insn, std::ostream& os, ppc_cpu_t dialect, uint32_t memaddr, SymbolGetter symGetter);
bool skip_optional_operands (const ppc_opindex_t *opindex,
			uint64_t insn, ppc_cpu_t dialect, bool *is_pcrel);