
#pragma once

/* The zero index is used to indicate the end of the list of
   operands.  */
#define UNUSED 0

  /* The BA field in an XL form instruction.  */
#define BA UNUSED + 1
  /* The BI field in a B form or XL form instruction.  */
#define BI BA
#define BI_MASK (0x1f << 16)

  /* The BT, BA and BB fields in a XL form instruction when they must all
     be the same.  */
#define BTAB BA + 1

  /* The BB field in an XL form instruction.  */
#define BB BTAB + 1
#define BB_MASK (0x1f << 11)

  /* The BA and BB fields in a XL form instruction when they must be
     the same.  */
#define BAB BB + 1

  /* The VRA and VRB fields in a VX form instruction when they must be the same.
     This is used for extended mnemonics like vmr.  */
#define VAB BAB + 1

  /* The RA and RB fields in a VX form instruction when they must be the same.
     This is used for extended mnemonics like evmr.  */
#define RAB VAB + 1
#define BC RAB + 1

  /* The BD field in a B form instruction.  The lower two bits are
     forced to zero.  */
#define BD BC + 1

  /* The BD field in a B form instruction when absolute addressing is
     used.  */
#define BDA BD + 1

  /* The BD field in a B form instruction when the - modifier is used.
     This sets the y bit of the BO field appropriately.  */
#define BDM BDA + 1

  /* The BD field in a B form instruction when the - modifier is used
     and absolute address is used.  */
#define BDMA BDM + 1

  /* The BD field in a B form instruction when the + modifier is used.
     This sets the y bit of the BO field appropriately.  */
#define BDP BDMA + 1

  /* The BD field in a B form instruction when the + modifier is used
     and absolute addressing is used.  */
#define BDPA BDP + 1

  /* The BF field in an X or XL form instruction.  */
#define BF BDPA + 1
  /* The CRFD field in an X form instruction.  */
#define CRFD BF
  /* The CRD field in an XL form instruction.  */
#define CRD BF

  /* The BF field in an X or XL form instruction.  */
#define BFF BF + 1

  /* The ACC field in a VSX ACC 8LS:D-form instruction.  */
#define ACC BFF + 1

  /* An optional BF field.  This is used for comparison instructions,
     in which an omitted BF field is taken as zero.  */
#define OBF ACC + 1

  /* The BFA field in an X or XL form instruction.  */
#define BFA OBF + 1

  /* The BO field in a B form instruction.  Certain values are
     illegal.  */
#define BO BFA + 1
#define BO_MASK (0x1f << 21)

  /* The BO field in a B form instruction when the - modifier is used.  */
#define BOM BO + 1

  /* The BO field in a B form instruction when the + modifier is used.  */
#define BOP BOM + 1

  /* The RM field in an X form instruction.  */
#define RM BOP + 1
#define DD RM
#define BH RM + 1

  /* The BT field in an X or XL form instruction.  */
#define BT BH + 1

  /* The BT field in a mtfsb0 or mtfsb1 instruction.  */
#define BTF BT + 1

  /* The BI16 field in a BD8 form instruction.  */
#define BI16 BTF + 1

  /* The BI32 field in a BD15 form instruction.  */
#define BI32 BI16 + 1

  /* The BO32 field in a BD15 form instruction.  */
#define BO32 BI32 + 1

  /* The B8 field in a BD8 form instruction.  */
#define B8 BO32 + 1

  /* The B15 field in a BD15 form instruction.  The lowest bit is
     forced to zero.  */
#define B15 B8 + 1

  /* The B24 field in a BD24 form instruction.  The lowest bit is
     forced to zero.  */
#define B24 B15 + 1

  /* The condition register number portion of the BI field in a B form
     or XL form instruction.  This is used for the extended
     conditional branch mnemonics, which set the lower two bits of the
     BI field.  This field is optional.  */
#define CR B24 + 1

  /* The CRB field in an X form instruction.  */
#define CRB CR + 1
  /* The MB field in an M form instruction.  */
#define MB CRB
#define MB_MASK (0x1f << 6)
  /* The CRD32 field in an XL form instruction.  */
#define CRD32 CRB + 1
  /* The CRFS field in an X form instruction.  */
#define CRFS CRD32 + 1
#define CRS CRFS + 1
  /* The CT field in an X form instruction.  */
#define CT CRS + 1
  /* The MO field in an mbar instruction.  */
#define MO CT
  /* The TH field in dcbtct.  */
#define THCT CT + 1
  /* The TH field in dcbtds.  */
#define THDS THCT + 1
  /* The D field in a D form instruction.  This is a displacement off
     a register, and implies that the next operand is a register in
     parentheses.  */
#define D THDS + 1
  /* The D8 field in a D form instruction.  This is a displacement off
     a register, and implies that the next operand is a register in
     parentheses.  */
#define D8 D + 1
  /* The DCMX field in an X form instruction.  */
#define DCMX D8 + 1
  /* The split DCMX field in an X form instruction.  */
#define DCMXS DCMX + 1
  /* The DQ field in a DQ form instruction.  This is like D, but the
     lower four bits are forced to zero. */
#define DQ DCMXS + 1
  /* The DS field in a DS form instruction.  This is like D, but the
     lower two bits are forced to zero.  */
#define DS DQ + 1
  /* The D field in an 8-byte D form prefix instruction.  This is a displacement
     off a register, and implies that the next operand is a register in
     parentheses.  */
#define D34 DS + 1

  /* The SI field in an 8-byte D form prefix instruction.  */
#define SI34 D34 + 1

  /* The NSI field in an 8-byte D form prefix instruction.  This is the
     same as the SI34 field, only negated.  */
#define NSI34 SI34 + 1

  /* The IMM32 field in a vector splat immediate prefix instruction.  */
#define IMM32 NSI34 + 1

  /* The UIM field in a vector permute extended prefix instruction.  */
#define UIM3 IMM32 + 1

  /* The UIM field in a vector eval prefix instruction.  */
#define UIM8 UIM3 + 1

  /* The IX field in xxsplti32dx.  */
#define IX UIM8 + 1

  /* The PMSK field in GER rank 8 prefix instructions.  */
#define PMSK8 IX + 1

  /* The PMSK field in GER rank 4 prefix instructions.  */
#define PMSK4 PMSK8 + 1

  /* The PMSK field in GER rank 2 prefix instructions.  */
#define PMSK2 PMSK4 + 1

  /* The XMSK field in GER prefix instructions.  */
#define XMSK PMSK2 + 1

  /* The YMSK field in GER prefix instructions.  */
#define YMSK XMSK + 1

  /* The YMSK field in 64-bit GER prefix instructions.  */
#define YMSK2 YMSK + 1

  /* The DUIS or BHRBE fields in a XFX form instruction, 10 bits
     unsigned imediate */
#define DUIS YMSK2 + 1
#define BHRBE DUIS

  /* The split DW field in a X form instruction.  */
#define DW DUIS + 1

  /* The split D field in a DX form instruction.  */
#define DXD DW + 1

  /* The split ND field in a DX form instruction.
     This is the same as the DX field, only negated.  */
#define NDXD DXD + 1

  /* The E field in a wrteei instruction.  */
  /* And the W bit in the pair singles instructions.  */
  /* And the ST field in a VX form instruction.  */
#define E NDXD + 1
#define PSW E
#define ST E

  /* The FL1 field in a POWER SC form instruction.  */
#define FL1 E + 1
  /* The U field in an X form instruction.  */
#define U FL1

  /* The FL2 field in a POWER SC form instruction.  */
#define FL2 FL1 + 1

  /* The FLM field in an XFL form instruction.  */
#define FLM FL2 + 1

  /* The FRA field in an X or A form instruction.  */
#define FRA FLM + 1
#define FRA_MASK (0x1f << 16)

  /* The FRAp field of DFP instructions.  */
#define FRAp FRA + 1

  /* The FRB field in an X or A form instruction.  */
#define FRB FRAp + 1
#define FRB_MASK (0x1f << 11)

  /* The FRBp field of DFP instructions.  */
#define FRBp FRB + 1

  /* The FRC field in an A form instruction.  */
#define FRC FRBp + 1
#define FRC_MASK (0x1f << 6)

  /* The FRS field in an X form instruction or the FRT field in a D, X
     or A form instruction.  */
#define FRS FRC + 1
#define FRT FRS

  /* The FRSp field of stfdp or the FRTp field of lfdp and DFP
     instructions.  */
#define FRSp FRS + 1
#define FRTp FRSp

  /* The FXM field in an XFX instruction.  */
#define FXM FRSp + 1

  /* Power4 version for mfcr.  */
#define FXM4 FXM + 1

  /* The IMM20 field in an LI instruction.  */
#define IMM20 FXM4 + 1

  /* The L field in a D or X form instruction.  */
#define L IMM20 + 1

  /* The optional L field in tlbie and tlbiel instructions.  */
#define LOPT L + 1
  /* The R field in a HTM X form instruction.  */
#define HTM_R LOPT

  /* The optional L field in the paste. instruction. This is similar to LOPT
     above, but with a default value of 1.  */
#define L1OPT LOPT + 1

  /* The optional (for 32-bit) L field in cmp[l][i] instructions.  */
#define L32OPT L1OPT + 1

  /* The 2-bit L or WC field in an X (sync, dcbf or wait) form instruction.  */
#define L2OPT L32OPT + 1
#define LS L2OPT
#define WC L2OPT

  /* The LEV field in a POWER SVC / POWER9 SCV form instruction.  */
#define SVC_LEV L2OPT + 1

  /* The LEV field in an SC form instruction.  */
#define LEV SVC_LEV + 1

  /* The LI field in an I form instruction.  The lower two bits are
     forced to zero.  */
#define LI LEV + 1

  /* The LI field in an I form instruction when used as an absolute
     address.  */
#define LIA LI + 1

  /* The 3-bit L field in a sync or dcbf instruction.  */
#define LS3 LIA + 1
#define L3OPT LS3

  /* The ME field in an M form instruction.  */
#define ME LS3 + 1
#define ME_MASK (0x1f << 1)

#define CRWn ME + 1

#define ELWn CRWn + 1

#define ERWn ELWn + 1

#define ERWb ERWn + 1

#define CSLWb ERWb + 1

#define CSLWn CSLWb + 1

#define ILWn CSLWn + 1

#define ILWb ILWn + 1

#define IRWn ILWb + 1

#define IRWb IRWn + 1

  /* The MB and ME fields in an M form instruction expressed a single
     operand which is a bitmask indicating which bits to select.  This
     is a two operand form using PPC_OPERAND_NEXT.  See the
     description in opcode/ppc.h for what this means.  */
#define MBE IRWb + 1

  /* The MB or ME field in an MD or MDS form instruction.  The high
     bit is wrapped to the low end.  */
#define MB6 MBE + 2
#define ME6 MB6
#define MB6_MASK (0x3f << 5)

#define ELDn MB6 + 1

#define ERDn ELDn + 1

#define CRDn ERDn + 1

  /* The NB field in an X form instruction.  The value 32 is stored as
     0.  */
#define NB CRDn + 1

  /* The NBI field in an lswi instruction, which has special value
     restrictions.  The value 32 is stored as 0.  */
#define NBI NB + 1

  /* The NSI field in a D form instruction.  This is the same as the
     SI field, only negated.  */
#define NSI NBI + 1

  /* The NSI field in a D form instruction when we accept a wide range
     of positive values.  */
#define NSISIGNOPT NSI + 1

  /* The RA field in an D, DS, DQ, X, XO, M, or MDS form instruction.  */
#define RA NSISIGNOPT + 1
#define RA_MASK (0x1f << 16)

  /* As above, but 0 in the RA field means zero, not r0.  */
#define RA0 RA + 1

  /* Similar to above, but optional.  */
#define PRA0 RA0 + 1

  /* The RA field in the DQ form lq or an lswx instruction, which have
     special value restrictions.  */
#define RAQ PRA0 + 1
#define RAX RAQ

  /* Similar to above, but optional.  */
#define PRAQ RAQ + 1

  /* The R field in an 8-byte D, DS, DQ or X form prefix instruction.  */
#define PCREL PRAQ + 1
#define PCREL_MASK (1ULL << 52)

#define PCREL0 PCREL + 1

  /* The RA field in a D or X form instruction which is an updating
     load, which means that the RA field may not be zero and may not
     equal the RT field.  */
#define RAL PCREL0 + 1

  /* The RA field in an lmw instruction, which has special value
     restrictions.  */
#define RAM RAL + 1

  /* The RA field in a D or X form instruction which is an updating
     store or an updating floating point load, which means that the RA
     field may not be zero.  */
#define RAS RAM + 1

  /* The RA field of the tlbwe, dccci and iccci instructions,
     which are optional.  */
#define RAOPT RAS + 1

  /* The RB field in an X, XO, M, or MDS form instruction.  */
#define RB RAOPT + 1
#define RB_MASK (0x1f << 11)

  /* The RS and RB fields in an X form instruction when they must be the same.
     This is used for extended mnemonics like mr.  */
#define RSB RB + 1

  /* The RB field in an lswx instruction, which has special value
     restrictions.  */
#define RBX RSB + 1

  /* The RB field of the dccci and iccci instructions, which are optional.  */
#define RBOPT RBX + 1

  /* The RC register field in an maddld, maddhd or maddhdu instruction.  */
#define RC RBOPT + 1

  /* The RS field in a D, DS, X, XFX, XS, M, MD or MDS form
     instruction or the RT field in a D, DS, X, XFX or XO form
     instruction.  */
#define RS RC + 1
#define RT RS
#define RT_MASK (0x1f << 21)
#define RD RS

#define RD_EVEN RS + 1
#define RS_EVEN RD_EVEN

  /* The RS and RT fields of the DS form stq and DQ form lq instructions,
     which have special value restrictions.  */
#define RSQ RS_EVEN + 1
#define RTQ RSQ
#define Q_MASK (1 << 21)

  /* The RS field of the tlbwe instruction, which is optional.  */
#define RSO RSQ + 1
#define RTO RSO

  /* The RX field of the SE_RR form instruction.  */
#define RX RSO + 1

  /* The ARX field of the SE_RR form instruction.  */
#define ARX RX + 1

  /* The RY field of the SE_RR form instruction.  */
#define RY ARX + 1
#define RZ RY

  /* The ARY field of the SE_RR form instruction.  */
#define ARY RY + 1

  /* The SCLSCI8 field in a D form instruction.  */
#define SCLSCI8 ARY + 1

  /* The SCLSCI8N field in a D form instruction.  This is the same as the
     SCLSCI8 field, only negated.  */
#define SCLSCI8N SCLSCI8 + 1

  /* The SD field of the SD4 form instruction.  */
#define SE_SD SCLSCI8N + 1

  /* The SD field of the SD4 form instruction, for halfword.  */
#define SE_SDH SE_SD + 1

  /* The SD field of the SD4 form instruction, for word.  */
#define SE_SDW SE_SDH + 1

  /* The SH field in an X or M form instruction.  */
#define SH SE_SDW + 1
#define SH_MASK (0x1f << 11)
  /* The other UIMM field in a EVX form instruction.  */
#define EVUIMM SH
  /* The FC field in an atomic X form instruction.  */
#define FC SH
#define UIM5 SH

#define RRWn SH + 1

#define SLWn RRWn + 1

#define SRWn SLWn + 1

#define EVUIMM_LT8 SRWn + 1

#define EVUIMM_LT16 EVUIMM_LT8 + 1

  /* The SI field in a HTM X form instruction.  */
#define HTM_SI EVUIMM_LT16 + 1

  /* The SH field in an MD form instruction.  This is split.  */
#define SH6 HTM_SI + 1
#define SH6_MASK ((0x1f << 11) | (1 << 1))

#define RRDn SH6 + 1

#define SLDn RRDn + 1

#define SRDn SLDn + 1

#define ERDb SRDn + 1

#define CSLDn ERDb + 1

#define CSLDb CSLDn + 1

#define IRDn CSLDb + 1

#define IRDb IRDn + 1

  /* The SH field of some variants of the tlbre and tlbwe
     instructions, and the ELEV field of the e_sc instruction.  */
#define SHO IRDb + 1
#define ELEV SHO

  /* The SI field in a D form instruction.  */
#define SI SHO + 1

  /* The SI field in a D form instruction when we accept a wide range
     of positive values.  */
#define SISIGNOPT SI + 1

  /* The SI8 field in a D form instruction.  */
#define SI8 SISIGNOPT + 1

  /* The SPR field in an XFX form instruction.  This is flipped--the
     lower 5 bits are stored in the upper 5 and vice- versa.  */
#define SPR SI8 + 1
#define PMR SPR
#define TMR SPR
#define SPR_MASK (0x3ff << 11)

  /* The BAT index number in an XFX form m[ft]ibat[lu] instruction.  */
#define SPRBAT SPR + 1
#define SPRBAT_MASK (0xc1 << 11)

  /* The GQR index number in an XFX form m[ft]gqr instruction.  */
#define SPRGQR SPRBAT + 1
#define SPRGQR_MASK (0x7 << 16)

  /* The SPRG register number in an XFX form m[ft]sprg instruction.  */
#define SPRG SPRGQR + 1

  /* The SR field in an X form instruction.  */
#define SR SPRG + 1
  /* The 4-bit UIMM field in a VX form instruction.  */
#define UIMM4 SR

  /* The STRM field in an X AltiVec form instruction.  */
#define STRM SR + 1
  /* The T field in a tlbilx form instruction.  */
#define T STRM
  /* The L field in wclr instructions.  */
#define L2 STRM

  /* The ESYNC field in an X (sync) form instruction.  */
#define ESYNC STRM + 1

  /* The SV field in a POWER SC form instruction.  */
#define SV ESYNC + 1

  /* The TBR field in an XFX form instruction.  This is like the SPR
     field, but it is optional.  */
#define TBR SV + 1

  /* The TO field in a D or X form instruction.  */
#define TO TBR + 1
#define DUI TO
#define TO_MASK (0x1f << 21)

  /* The UI field in a D form instruction.  */
#define UI TO + 1

#define UISIGNOPT UI + 1

  /* The IMM field in an SE_IM5 instruction.  */
#define UI5 UISIGNOPT + 1

  /* The OIMM field in an SE_OIM5 instruction.  */
#define OIMM5 UI5 + 1

  /* The UI7 field in an SE_LI instruction.  */
#define UI7 OIMM5 + 1

  /* The VA field in a VA, VX or VXR form instruction.  */
#define VA UI7 + 1

  /* The VB field in a VA, VX or VXR form instruction.  */
#define VB VA + 1

  /* The VC field in a VA form instruction.  */
#define VC VB + 1

  /* The VD or VS field in a VA, VX, VXR or X form instruction.  */
#define VD VC + 1
#define VS VD

  /* The SIMM field in a VX form instruction, and TE in Z form.  */
#define SIMM VD + 1
#define TE SIMM

  /* The UIMM field in a VX form instruction.  */
#define UIMM SIMM + 1
#define DCTL UIMM

  /* The 3-bit UIMM field in a VX form instruction.  */
#define UIMM3 UIMM + 1

  /* The 6-bit UIM field in a X form instruction.  */
#define UIM6 UIMM3 + 1

  /* The SIX field in a VX form instruction.  */
#define SIX UIM6 + 1
#define MMMM SIX

  /* The PS field in a VX form instruction.  */
#define PS SIX + 1

  /* The SH field in a vector shift double by bit immediate instruction.  */
#define SH3 PS + 1

  /* The SHB field in a VA form instruction.  */
#define SHB SH3 + 1

  /* The other UIMM field in a half word EVX form instruction.  */
#define EVUIMM_1 SHB + 1

#define EVUIMM_1_EX0 EVUIMM_1 + 1

#define EVUIMM_2 EVUIMM_1_EX0 + 1

#define EVUIMM_2_EX0 EVUIMM_2 + 1

  /* The other UIMM field in a word EVX form instruction.  */
#define EVUIMM_4 EVUIMM_2_EX0 + 1

#define EVUIMM_4_EX0 EVUIMM_4 + 1

  /* The other UIMM field in a double EVX form instruction.  */
#define EVUIMM_8 EVUIMM_4_EX0 + 1

#define EVUIMM_8_EX0 EVUIMM_8 + 1

  /* The WS or DRM field in an X form instruction.  */
#define WS EVUIMM_8_EX0 + 1
#define DRM WS
  /* The NNN field in a VX form instruction for SPE2  */
#define NNN WS

  /* PowerPC paired singles extensions.  */
  /* W bit in the pair singles instructions for x type instructions.  */
#define PSWM WS + 1
  /* The BO16 field in a BD8 form instruction.  */
#define BO16 PSWM

  /* IDX bits for quantization in the pair singles instructions.  */
#define PSQ PSWM + 1

  /* IDX bits for quantization in the pair singles x-type instructions.  */
#define PSQM PSQ + 1

  /* Smaller D field for quantization in the pair singles instructions.  */
#define PSD PSQM + 1

  /* The L field in an mtmsrd or A form instruction or R or W in an
     X form.  */
#define A_L PSD + 1
#define W A_L
#define X_R A_L

  /* The RMC or CY field in a Z23 form instruction.  */
#define RMC A_L + 1
#define CY RMC

#define R RMC + 1
#define MP R

#define RIC R + 1

#define PRS RIC + 1

#define SP PRS + 1

#define S SP + 1

  /* The S field in a XL form instruction.  */
#define SXL S + 1

  /* SH field starting at bit position 16.  */
#define SH16 SXL + 1
  /* The DCM and DGM fields in a Z form instruction.  */
#define DCM SH16
#define DGM DCM

  /* The EH field in larx instruction.  */
#define EH SH16 + 1

  /* The L field in an mtfsf or XFL form instruction.  */
  /* The A field in a HTM X form instruction.  */
#define XFL_L EH + 1
#define HTM_A XFL_L

  /* Xilinx APU related masks and macros */
#define FCRT XFL_L + 1
#define FCRT_MASK (0x1f << 21)

  /* Xilinx FSL related masks and macros */
#define FSL FCRT + 1
#define FSL_MASK (0x1f << 11)

  /* Xilinx UDI related masks and macros */
#define URT FSL + 1

#define URA URT + 1

#define URB URA + 1

#define URC URB + 1

  /* The VLESIMM field in a D form instruction.  */
#define VLESIMM URC + 1

  /* The VLENSIMM field in a D form instruction.  */
#define VLENSIMM VLESIMM + 1

  /* The VLEUIMM field in a D form instruction.  */
#define VLEUIMM VLENSIMM + 1

  /* The VLEUIMML field in a D form instruction.  */
#define VLEUIMML VLEUIMM + 1

  /* The XT and XS fields in an XX1 or XX3 form instruction.  This is
     split.  */
#define XS6 VLEUIMML + 1
#define XT6 XS6

  /* The XT and XS fields in an DQ form VSX instruction.  This is split.  */
#define XSQ6 XT6 + 1
#define XTQ6 XSQ6

  /* The split XTp field in a vector paired instruction.  */
#define XTP XSQ6 + 1

#define XTS XTP + 1

  /* The XT field in a plxv instruction.  Runs into the OP field.  */
#define XTOP XTS + 1

  /* The XA field in an XX3 form instruction.  This is split.  */
#define XA6 XTOP + 1

  /* The XA field in an MMA XX3 form instruction.  This is split and
     must not overlap with the ACC operand.  */
#define XA6a XA6 + 1

  /* The XAp field in an MMA XX3 form instruction.  This is split.
     This is like XA6a, but must be even.  */
#define XA6ap XA6a + 1

  /* The XB field in an XX2 or XX3 form instruction.  This is split.  */
#define XB6 XA6ap + 1

  /* The XB field in an XX3 form instruction.  This is split and
     must not overlap with the ACC operand.  */
#define XB6a XB6 + 1

  /* The XA and XB fields in an XX3 form instruction when they must be the same.
     This is used in extended mnemonics like xvmovdp.  This is split.  */
#define XAB6 XB6a + 1

  /* The XC field in an XX4 form instruction.  This is split.  */
#define XC6 XAB6 + 1

  /* The DM or SHW field in an XX3 form instruction.  */
#define DM XC6 + 1
#define SHW DM

  /* The DM field in an extended mnemonic XX3 form instruction.  */
#define DMEX DM + 1

  /* The UIM field in an XX2 form instruction.  */
#define UIM DMEX + 1
  /* The 2-bit UIMM field in a VX form instruction.  */
#define UIMM2 UIM
  /* The 2-bit L field in a darn instruction.  */
#define LRAND UIM

#define ERAT_T UIM + 1

#define IH ERAT_T + 1

  /* The 2-bit SC or PL field in an X form instruction.  */
#define SC2 IH + 1
#define PL SC2

  /* The 8-bit IMM8 field in a XX1 form instruction.  */
#define IMM8 SC2 + 1

#define VX_OFF IMM8 + 1

#define VX_OFF_SPE2 VX_OFF + 1

#define BBB VX_OFF_SPE2 + 1

#define DDD BBB + 1
#define VX_MASK_DDD  (VX_MASK & ~0x1)

#define HH DDD + 1