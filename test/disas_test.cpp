#include <gtest/gtest.h>
#include <cstdint>
#include <iostream>
#include <ios>

#include "ppcdisasm/ppc-dis.hpp"
#include "ppcdisasm/ppc-operands.h"

TEST(DisasTest, OneInsnDecode) {
  uint32_t insn = 0x3816FFFF;
  
  disassemble_init_powerpc();
  const struct powerpc_opcode* opcode = lookup_powerpc (insn, ppc_750cl_dialect);
  int64_t rt = operand_value_powerpc(RT, insn, ppc_750cl_dialect);
  int64_t ra = operand_value_powerpc(RA0, insn, ppc_750cl_dialect);
  int64_t si = operand_value_powerpc(SI, insn, ppc_750cl_dialect);

  EXPECT_STREQ(opcode->name, "addi");
  EXPECT_EQ(rt, 0);
  EXPECT_EQ(ra, 22);
  EXPECT_EQ(si, -1);
}

TEST(DisasTest, OneInsnDisasm) {
  uint32_t insn = 0x3816FFFF;
  ppc_cpu_t dialect = ppc_750cl_dialect;
  uint32_t memaddr = 0x80000000;
  
  disassemble_init_powerpc();
  std::stringstream ss;
  SymbolGetter symGetter = [](uint32_t addr) -> std::string {
    std::stringstream ss("lab_");
    ss << std::hex << addr;
    return ss.str();
  };
  cout_insn_powerpc(insn, ss, dialect, memaddr, symGetter);

  EXPECT_STREQ(ss.str().c_str(), "addi    r0,r22,-1");
}