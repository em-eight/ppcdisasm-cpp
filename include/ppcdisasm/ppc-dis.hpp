
#pragma once

extern "C" {
#include "opcode/ppc.h"
}
#include <iostream>
#include <string>
#include <functional>

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
 * Relocation: kind of potential needed suffix
*/
enum RelocationKind {
  NO_RELOC=0, // No relocation in this insn
  PPC_HA, // @ha
  PPC_HI, // @h
  PPC_L, // @l
  PPC_SDA21, // @sda21
  ABSOLUTE,
};

/**
 * @brief
 * The result of a symbol lookup. Use RELOC_TYPE_NONE if no relocation targets this instruction
*/
struct RelocationType {
  RelocationKind kind;
  std::string name;
  RelocationType(RelocationKind kind, std::string name) : kind(kind), name(name) {}
};
extern RelocationType RELOC_TYPE_NONE;

// Symbol lookup: gets address and returns the corresponding RelocationType
typedef std::function<RelocationType(uint32_t)> SymbolGetter;
// Just returns RELOC_TYPE_NONE
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
 * @brief Write the disassembled instruction to the provided std::ostream
*/
int cout_insn_powerpc(uint64_t insn, std::ostream& os, ppc_cpu_t dialect,
    RelocStyle relocStyle=RELOC_STYLE_NO_RELOCS, uint32_t memaddr=0x0, SymbolGetter symbolGetter=defaultSymbolGetter);
/* Specifies if an opcode's operand can be skipped */
bool skip_optional_operands (const ppc_opindex_t *opindex,
			uint64_t insn, ppc_cpu_t dialect, bool *is_pcrel);