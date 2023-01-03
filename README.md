# ppcdisasm
![build badge](https://github.com/em-eight/ppcdisasm-cpp/actions/workflows/test.yml/badge.svg?branch=main)

A C++ 32-bit PPC disassembler based on libopcodes

## Building/Installation
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
make install
```
You may need to adjust your PATH/LD_LIBRARY_PATH to the path of the installed executables/libraries.

## Usage
```cpp
#include "ppcdisasm/ppc-dis.hpp"

// Call this before any disassembly call
disassemble_init_powerpc();

uint32_t insn = 0x3816FFFF;
ppc_cpu_t dialect = ppc_750cl_dialect;
  
// decode instruction
const struct powerpc_opcode* opcode = lookup_powerpc(insn, ppc_750cl_dialect);
const char* opcode_name = opcode->name;
int64_t rt = operand_value_powerpc(RT, insn, ppc_750cl_dialect);
int64_t ra = operand_value_powerpc(RA0, insn, ppc_750cl_dialect);
int64_t si = operand_value_powerpc(SI, insn, ppc_750cl_dialect);

// simple disassembly, no relocations
std::stringstream ss;
cout_insn_powerpc(insn, ss, dialect);

// not so simple disassembly, symbol lookup and relocation formatting
RelocStyle relocStyle = RELOC_STYLE_GAS;
uint32_t vma = 0x80000000;
SymbolGetter mySymbolGetter = [](uint32_t address) { 
    MySymbolType symbol = mySymbolLookup(address);
    return { symbol.name, symbol.relocKind };
};
cout_insn_powerpc(insn, ss, dialect, relocStyle, vma, mySymbolGetter);
```

## Testing
```
cmake -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Release ..
make
ctest
```

## Documentation
`opcode/ppc.h`, `ppcdisasm/ppc-dis.hpp` and `ppcdisasm/ppc-operands.h` have everything you need

## Performance
After correctness, the next highest priority is performance.
Tests on a Ryzen 7-5700G:
- Decode: 12M instruction/s (48 MB/s)
- Disassemble: 2.6M instruction/s (10.4 MB/s)