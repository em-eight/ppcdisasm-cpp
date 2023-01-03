
#include <cstdint>
#include <iostream>
#include <fstream>
#include <chrono>

#include "ppcdisasm/ppc-dis.hpp"
#include "ppcdisasm/ppc-operands.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Expected input instruction binary" << std::endl;
  }

  char* filename = argv[1];
  std::ifstream istrm(filename, std::ios::in | std::ios::binary | std::ios::ate);
  const int64_t size = istrm.tellg();
  istrm.seekg (0, std::ios::beg);
  if (!istrm.is_open()) {
    std::cout << "failed to open " << filename << '\n';
    exit(-1);
  }
  std::cout << filename << " " << size << std::endl;

  uint32_t insn;
  uint32_t total_insn = size/sizeof(insn);
  std::vector<uint32_t> insns(total_insn);
  uint32_t idx = 0;
  while (istrm) {
    istrm.read(reinterpret_cast<char *>(&insn), sizeof(insn));
    insns[idx] = __builtin_bswap32(insn);
    idx++;
  }

  using namespace std::chrono;
  steady_clock::time_point t1 = steady_clock::now();
  disassemble_init_powerpc();
  ppc_cpu_t dialect = ppc_750cl_dialect;
  steady_clock::time_point t2 = steady_clock::now();
  for (uint32_t i= 0; i < size/sizeof(insn); i++) {
    insn = insns[i];
    const struct powerpc_opcode* opcode = lookup_powerpc (insn, dialect);

    const ppc_opindex_t *opindex;
    const struct powerpc_operand *operand;
    for (opindex = opcode->operands; *opindex != 0; opindex++)
    {
      bool skip_optional = false;
      bool is_pcrel = false;

      operand = powerpc_operands + *opindex;

      /* If all of the optional operands past this one have their
        default value, then don't print any of them.  Except in
        raw mode, print them all.  */
      if ((operand->flags & PPC_OPERAND_OPTIONAL) != 0
          && (ppc_750cl_dialect & PPC_OPCODE_RAW) == 0)
        {
          if (!skip_optional)
            skip_optional = skip_optional_operands (opindex, insn, dialect, &is_pcrel);
          if (skip_optional)
            continue;
        }
        int64_t value = operand_value_powerpc (operand, insn, dialect);
      }
  }
  steady_clock::time_point t3 = steady_clock::now();

  duration<double> initialization = duration_cast<duration<double>>(t2 - t1);
  duration<double> decode = duration_cast<duration<double>>(t3 - t2);
  duration<double> all = duration_cast<duration<double>>(t3 - t1);
  std::cout << "Initialization: " << initialization.count() << std::endl;
  std::cout << "Decode: " << total_insn/(decode.count()*1e6) << "M insn/s" << std::endl;
  std::cout << "All: " << total_insn/(all.count()*1e6) << "M insn/s" << std::endl;
}