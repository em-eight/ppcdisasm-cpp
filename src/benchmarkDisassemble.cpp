
#include <cstdint>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>

#include "ppcdisasm/ppc-dis.hpp"
#include "ppcdisasm/ppc-operands.h"

int main(int argc, char** argv) {
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
  std::stringstream ss;
  SymbolGetter symGetter = [](uint32_t addr) -> std::string {
    std::stringstream ss("lab_");
    ss << std::hex << addr;
    return ss.str();
  };
  uint32_t memaddr = 0x80000000;
  steady_clock::time_point t2 = steady_clock::now();
  for (uint32_t i= 0; i < size/sizeof(insn); i++) {
    insn = insns[i];
    cout_insn_powerpc(insn, ss, dialect, memaddr, symGetter);
    memaddr += 4;
    ss << "\n";
  }
  // write to output file
  // std::ofstream of("tmp.txt");
  // of << ss.rdbuf();
  steady_clock::time_point t3 = steady_clock::now();

  duration<double> initialization = duration_cast<duration<double>>(t2 - t1);
  duration<double> decode = duration_cast<duration<double>>(t3 - t2);
  duration<double> all = duration_cast<duration<double>>(t3 - t1);
  std::cout << "Initialization: " << initialization.count() << std::endl;
  std::cout << "Disassemble: " << total_insn/(decode.count()*1e6) << "M insn/s" << std::endl;
  std::cout << "All: " << total_insn/(all.count()*1e6) << "M insn/s" << std::endl;
}