
#pragma once

extern "C" {
#include "opcode/ppc.h"
}
#include <iostream>
#include <string>
#include <functional>

namespace ppcdisasm {

/**
 * @brief
 * Style of relocation formats
*/
enum RelocStyle {
  RELOC_STYLE_NO_RELOCS,
  RELOC_STYLE_GAS,
  RELOC_STYLE_MWCC
};

/**
 * @brief
 * The result of a symbol lookup. Use RELOC_TARGET_NONE if no relocation targets this instruction
*/
struct RelocationTarget {
  // kind values defined in ppc-relocations.hpp
  int32_t kind;
  std::string name;
  RelocationTarget(int32_t kind, std::string name) : kind(kind), name(name) {}
};
extern RelocationTarget RELOC_TARGET_NONE;

// Symbol lookup: gets address and returns the corresponding RelocationTarget
typedef std::function<RelocationTarget(uint32_t)> SymbolGetter;
// Just returns RELOC_TARGET_NONE
extern SymbolGetter defaultSymbolGetter;

// same for gekko and broadway
extern const ppc_cpu_t ppc_750cl_dialect;

/**
 * @brief
 * Init global structures needed. Must be called before any call for disassembly
*/
void disassemble_init_powerpc ();
/* Find a match for INSN in the opcode table, given machine DIALECT.  */
const struct powerpc_opcode* lookup_powerpc (uint64_t insn, ppc_cpu_t dialect);
/* Extract the operand value from the PowerPC or POWER instruction.  */
int64_t operand_value_powerpc (const struct powerpc_operand *operand, uint64_t insn, ppc_cpu_t dialect);
/**
 * @brief Extract operand value from instruction. See ppc-operands.h for all possible operands 
 *        and ppc-opc.c opcode_table for the operands used in each instruction
*/
inline int64_t operand_value_powerpc (uint32_t opindex, uint64_t insn, ppc_cpu_t dialect) 
    { return operand_value_powerpc(&powerpc_operands[opindex], insn, dialect); }
/**
 * @brief Get the mnemonic ID of the opcode (aka its index in the opcode table)
*/
inline int32_t get_mnemonic(const struct powerpc_opcode* opcode) {
  return opcode - powerpc_opcodes;
}

/**
 * @brief Write the decoded instruction disassembly to the provided std::ostream. opcode must be non-null!
*/
int cout_decoded_insn_powerpc(struct powerpc_opcode* opcode, uint64_t insn, std::ostream& os, ppc_cpu_t dialect,
    RelocStyle relocStyle=RELOC_STYLE_NO_RELOCS, uint32_t memaddr=0x0, SymbolGetter symbolGetter=defaultSymbolGetter);
/**
 * @brief Write the instruction disassembly to the provided std::ostream
*/
int cout_insn_powerpc(uint64_t insn, std::ostream& os, ppc_cpu_t dialect,
    RelocStyle relocStyle=RELOC_STYLE_NO_RELOCS, uint32_t memaddr=0x0, SymbolGetter symbolGetter=defaultSymbolGetter);
/* Specifies if an opcode's operand can be skipped */
bool skip_optional_operands (const ppc_opindex_t *opindex,
			uint64_t insn, ppc_cpu_t dialect, bool *is_pcrel);

}