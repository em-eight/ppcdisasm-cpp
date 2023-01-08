
#include <cstdint>
#include <algorithm>
#include <string>
#include <cstring>

#include "ppcdisasm/ppc-dis.hpp"


#include <iostream>
#include <fstream>
#include <string>

#include "ppcdisasm/ppc-dis.hpp"

// in ppc-dis.cpp
extern void cout_all_opcode_defines(std::ostream& os, ppc_cpu_t, std::string);
extern void cout_all_form_defines(std::ostream& os, ppc_cpu_t, std::string);
extern void cout_all_mnem_defines(std::ostream& os, ppc_cpu_t, std::string);

/**
 * Generates a defines file for each opcode/form/mnemonic
*/
int main(int argc, char** argv) {
  if (argc != 4) {
    std::cout << "Gimme 3 paths. One for the generated instructions, forms and extended mnemonics" << std::endl;
    exit(-1);
  }
  std::ofstream opcode_defines(argv[1]);
  std::ofstream form_defines(argv[2]);
  std::ofstream mnem_defines(argv[3]);

  disassemble_init_powerpc();

  ppc_cpu_t dialect = PPC_OPCODE_750;
  std::string dialect_prefix = "PPC750";

  //cout_all_opcode_defines(opcode_defines, dialect);
  cout_all_form_defines(form_defines, dialect, dialect_prefix);
  cout_all_mnem_defines(mnem_defines, dialect, dialect_prefix);
}