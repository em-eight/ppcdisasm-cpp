
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <cstdarg>
#ifndef ATTRIBUTE_UNUSED
#if GCC_VERSION >= 3004
#define ATTRIBUTE_UNUSED __attribute__ ((__unused__))
#else
#define ATTRIBUTE_UNUSED
#endif
#endif

#include "ppcdisasm/ppc-dis.hpp"

#define PPC_OPCD_SEGS (1 + PPC_OP (-1))
static unsigned short powerpc_opcd_indices[PPC_OPCD_SEGS + 1];
// same for gekko and broadway
const ppc_cpu_t ppc_750cl_dialect = PPC_OPCODE_PPC | PPC_OPCODE_750 | PPC_OPCODE_PPCPS;

/* Calculate opcode table indices to speed up disassembly,
   and init dialect.  */
void
disassemble_init_powerpc ()
{
  if (powerpc_opcd_indices[PPC_OPCD_SEGS] == 0)
    {
      unsigned seg, idx, op;

      /* PPC opcodes */ 
      for (seg = 0, idx = 0; seg <= PPC_OPCD_SEGS; seg++)
        {
          powerpc_opcd_indices[seg] = idx;
          for (; idx < powerpc_num_opcodes; idx++)
            if (seg < PPC_OP (powerpc_opcodes[idx].opcode))
              break;
        }
    }
}

/* Find a match for INSN in the opcode table, given machine DIALECT.  */
const struct powerpc_opcode *
lookup_powerpc (uint64_t insn, ppc_cpu_t dialect)
{
  const struct powerpc_opcode *opcode, *opcode_end;
  unsigned long op;

  /* Get the major opcode of the instruction.  */
  op = PPC_OP (insn);

  /* Find the first match in the opcode table for this major opcode.  */
  opcode_end = powerpc_opcodes + powerpc_opcd_indices[op + 1];
  for (opcode = powerpc_opcodes + powerpc_opcd_indices[op];
       opcode < opcode_end;
       ++opcode)
    {
      const ppc_opindex_t *opindex;
      const struct powerpc_operand *operand;
      int invalid;

      if ((insn & opcode->mask) != opcode->opcode
          || ((dialect & PPC_OPCODE_ANY) == 0
              && ((opcode->flags & dialect) == 0
                  || (opcode->deprecated & dialect) != 0))
          || (opcode->deprecated & dialect & PPC_OPCODE_RAW) != 0)
        continue;

      /* Check validity of operands.  */
      invalid = 0;
      for (opindex = opcode->operands; *opindex != 0; opindex++)
        {
          operand = powerpc_operands + *opindex;
          if (operand->extract)
            (*operand->extract) (insn, dialect, &invalid);
        }
      if (invalid)
        continue;

      return opcode;
    }

  return NULL;
}

/* When printing styled disassembler output, this describes what style
   should be used.  */

enum disassembler_style
{
  /* This is the default style, use this for any additional syntax
     (e.g. commas between operands, brackets, etc), or just as a default if
     no other style seems appropriate.  */
  dis_style_text,

  /* Use this for all instruction mnemonics, or aliases for mnemonics.
     These should be things that correspond to real machine
     instructions.  */
  dis_style_mnemonic,

  /* Some architectures include additional mnemonic like fields within the
     instruction operands, e.g. on aarch64 'add w16, w7, w1, lsl #2' where
     the 'lsl' is an additional piece of text that describes how the
     instruction should behave.  This sub-mnemonic style can be used for
     these pieces of text.  */
  dis_style_sub_mnemonic,

  /* For things that aren't real machine instructions, but rather
     assembler directives, e.g. .byte, etc.  */
  dis_style_assembler_directive,

  /* Use this for any register names.  This may or may-not include any
     register prefix, e.g. '$', '%', at the discretion of the target,
     though within each target the choice to include prefixes for not
     should be kept consistent.  If the prefix is not printed with this
     style, then dis_style_text should be used.  */
  dis_style_register,

  /* Use this for any constant values used within instructions or
     directives, unless the value is an absolute address, or an offset
     that will be added to an address (no matter where the address comes
     from) before use.  This style may, or may-not be used for any
     prefix to the immediate value, e.g. '$', at the discretion of the
     target, though within each target the choice to include these
     prefixes should be kept consistent.  */
  dis_style_immediate,

  /* The style for the numerical representation of an absolute address.
     Anything that is an address offset should use the immediate style.
     This style may, or may-not be used for any prefix to the immediate
     value, e.g. '$', at the discretion of the target, though within
     each target the choice to include these prefixes should be kept
     consistent.  */
  dis_style_address,

  /* The style for any constant value within an instruction or directive
     that represents an offset that will be added to an address before
     use.  This style may, or may-not be used for any prefix to the
     immediate value, e.g. '$', at the discretion of the target, though
     within each target the choice to include these prefixes should be
     kept consistent.  */
  dis_style_address_offset,

  /* The style for a symbol's name.  The numerical address of a symbol
     should use the address style above, this style is reserved for the
     name.  */
  dis_style_symbol,

  /* The start of a comment that runs to the end of the line.  Anything
     printed after a comment start might be styled differently,
     e.g. everything might be styled as a comment, regardless of the
     actual style used.  The disassembler itself should not try to adjust
     the style emitted for comment content, e.g. an address emitted within
     a comment should still be given dis_style_address, in this way it is
     up to the user of the disassembler to decide how comments should be
     styled.  */
  dis_style_comment_start
};


static int
fprintf_styled (FILE *f, enum disassembler_style style ATTRIBUTE_UNUSED,
                const char *fmt, ...) 
{
  int res; 
  va_list ap;

  va_start (ap, fmt);
  res = vfprintf (f, fmt, ap); 
  va_end (ap);

  return res; 
}
#include <iostream>

static void cout_styled(std::ostream& os, enum disassembler_style style ATTRIBUTE_UNUSED, const char *fmt, ...) {
  va_list ap;
  va_start (ap, fmt);
  char buf[32]; vsnprintf(buf, sizeof(buf), fmt, ap); 
  va_end(ap);
  os << buf;
}

static void cout_address(std::ostream& os, uint32_t address, SymbolGetter symGetter) {
  os << symGetter(address);
}

/* Extract the operand value from the PowerPC or POWER instruction.  */
int64_t
operand_value_powerpc (const struct powerpc_operand *operand,
		       uint64_t insn, ppc_cpu_t dialect)
{
  int64_t value;
  int invalid = 0;
  /* Extract the value from the instruction.  */
  if (operand->extract)
    value = (*operand->extract) (insn, dialect, &invalid);
  else
    {
      if (operand->shift >= 0)
	      value = (insn >> operand->shift) & operand->bitm;
      else
	      value = (insn << -operand->shift) & operand->bitm;
      if ((operand->flags & PPC_OPERAND_SIGNED) != 0)
      {
        /* BITM is always some number of zeros followed by some
          number of ones, followed by some number of zeros.  */
        uint64_t top = operand->bitm;
        /* top & -top gives the rightmost 1 bit, so this
          fills in any trailing zeros.  */
        top |= (top & -top) - 1;
        top &= ~(top >> 1);
        value = (value ^ top) - top;
      }
    }

  return value;
}

/* Determine whether the optional operand(s) should be printed.  */

bool
skip_optional_operands (const ppc_opindex_t *opindex,
			uint64_t insn, ppc_cpu_t dialect, bool *is_pcrel)
{
  const struct powerpc_operand *operand;
  int num_optional;

  for (num_optional = 0; *opindex != 0; opindex++)
    {
      operand = &powerpc_operands[*opindex];
      if ((operand->flags & PPC_OPERAND_NEXT) != 0)
	return false;
      if ((operand->flags & PPC_OPERAND_OPTIONAL) != 0)
	{
	  int64_t value = operand_value_powerpc (operand, insn, dialect);

	  if (operand->shift == 52)
	    *is_pcrel = value != 0;

	  /* Negative count is used as a flag to extract function.  */
	  --num_optional;
	  if (value != ppc_optional_operand_value (operand, insn, dialect,
						   num_optional))
	    return false;
	}
    }

  return true;
}

int cout_insn_powerpc(uint64_t insn, std::ostream& os, ppc_cpu_t dialect, uint32_t memaddr, SymbolGetter symGetter) {
  const struct powerpc_opcode* opcode = lookup_powerpc(insn, dialect);

  int insn_length = 4;
  if (opcode != nullptr) {
    const ppc_opindex_t *opindex;
    const struct powerpc_operand *operand;
    enum AsmSep{
      need_comma = 0,
      need_1space = 1,
      need_2spaces = 2,
      need_3spaces = 3,
      need_4spaces = 4,
      need_5spaces = 5,
      need_6spaces = 6,
      need_7spaces = 7,
      need_paren
    } op_separator;
    bool skip_optional;
    bool is_pcrel;
    uint64_t d34;
    int blanks;

    cout_styled(os, dis_style_mnemonic, "%s", opcode->name);
    /* gdb fprintf_styled_func doesn't return count printed.  */
    blanks = 8 - strlen (opcode->name);
    if (blanks <= 0)
    blanks = 1;

    /* Now extract and print the operands.  */
    op_separator = (AsmSep) blanks;
    skip_optional = false;
    is_pcrel = false;
    d34 = 0;
    for (opindex = opcode->operands; *opindex != 0; opindex++)
    {
      int64_t value;

      operand = powerpc_operands + *opindex;

      /* If all of the optional operands past this one have their
        default value, then don't print any of them.  Except in
        raw mode, print them all.  */
      if ((operand->flags & PPC_OPERAND_OPTIONAL) != 0
          && (dialect & PPC_OPCODE_RAW) == 0)
        {
          if (!skip_optional)
            skip_optional = skip_optional_operands (opindex, insn, dialect, &is_pcrel);
          if (skip_optional)
            continue;
        }

      value = operand_value_powerpc (operand, insn, dialect);

      if (op_separator == need_comma)
        cout_styled(os, dis_style_text, ",");
      else if (op_separator == need_paren)
        cout_styled(os, dis_style_text, "(");
      else
        cout_styled(os, dis_style_text, "%*s", op_separator, " ");

      /* Print the operand as directed by the flags.  */
      if ((operand->flags & PPC_OPERAND_GPR) != 0
          || ((operand->flags & PPC_OPERAND_GPR_0) != 0 && value != 0))
        cout_styled(os, dis_style_register, "r%" PRId64, value);
      else if ((operand->flags & PPC_OPERAND_FPR) != 0)
        cout_styled(os, dis_style_register, "f%" PRId64, value);
      else if ((operand->flags & PPC_OPERAND_VR) != 0)
        cout_styled(os, dis_style_register, "v%" PRId64, value);
      else if ((operand->flags & PPC_OPERAND_VSR) != 0)
        cout_styled(os, dis_style_register, "vs%" PRId64, value);
      else if ((operand->flags & PPC_OPERAND_ACC) != 0)
        cout_styled(os, dis_style_register, "a%" PRId64, value);
      else if ((operand->flags & PPC_OPERAND_RELATIVE) != 0)
        cout_address(os, memaddr + value, symGetter);
      else if ((operand->flags & PPC_OPERAND_ABSOLUTE) != 0)
        cout_address(os, (uint32_t) value & 0xffffffff, symGetter);
      else if ((operand->flags & PPC_OPERAND_FSL) != 0)
        cout_styled(os, dis_style_register, "fsl%" PRId64, value);
      else if ((operand->flags & PPC_OPERAND_FCR) != 0)
        cout_styled(os, dis_style_register, "fcr%" PRId64, value);
      else if ((operand->flags & PPC_OPERAND_UDI) != 0)
        cout_styled(os, dis_style_register, "%" PRId64, value);
      else if ((operand->flags & PPC_OPERAND_CR_REG) != 0
        && (operand->flags & PPC_OPERAND_CR_BIT) == 0
        && (((dialect & PPC_OPCODE_PPC) != 0)
            || ((dialect & PPC_OPCODE_VLE) != 0)))
        cout_styled(os, dis_style_register, "cr%" PRId64, value);
      else if ((operand->flags & PPC_OPERAND_CR_BIT) != 0
        && (operand->flags & PPC_OPERAND_CR_REG) == 0
        && (((dialect & PPC_OPCODE_PPC) != 0)
            || ((dialect & PPC_OPCODE_VLE) != 0))) {
          static const char *cbnames[4] = { "lt", "gt", "eq", "so" };
          int cr;
          int cc;

          cr = value >> 2;
          cc = value & 3;
          if (cr != 0) {
            cout_styled(os, dis_style_text, "4*");
            cout_styled(os, dis_style_register, "cr%d", cr);
            cout_styled(os, dis_style_text, "+");
          }

          cout_styled(os, dis_style_sub_mnemonic, "%s", cbnames[cc]);
      } else {
          /* An immediate, but what style?  */
          enum disassembler_style style;

          if ((operand->flags & PPC_OPERAND_PARENS) != 0)
            style = dis_style_address_offset;
          else
            style = dis_style_immediate;

          cout_styled(os, style, "%" PRId64, value);
        }

      if (operand->shift == 52)
        is_pcrel = value != 0;
      else if (operand->bitm == UINT64_C (0x3ffffffff))
        d34 = value;

      if (op_separator == need_paren)
        cout_styled(os, dis_style_text, ")");

      op_separator = need_comma;
      if ((operand->flags & PPC_OPERAND_PARENS) != 0)
        op_separator = need_paren;
    }

    /* We have found and printed an instruction.  */
    return insn_length;
  }

  /* We could not find a match.  */
  cout_styled(os, dis_style_assembler_directive, ".long");
  cout_styled(os, dis_style_text, " ");
  cout_styled(os, dis_style_immediate, "0x%x", (uint64_t) insn);

  return insn_length;
}