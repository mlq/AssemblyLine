/**
 * Copyright 2021 University of Adelaide
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*defines all enumerators used in assemblyline*/
#ifndef ENUMS_H
#define ENUMS_H

typedef enum { BEGIN, FIRST_CH, SPACE_FOUND } filter_op;

// used to identify special opcodes (must be greater than 255 to avoid conflict
// with instruction opcode)
typedef enum {

  none = 0,
  SIB = 0x24,
  REG = 256,
  REX,
  VEX,
  EVEX,
  W0,
  MEM,
  NO_PREFIX = 399
} op_encoding;

// only used for determining what prefix to use based on registers
typedef enum {

  rex = 0x40,
  rex_w = 0x48,
  rex_b = 0x01,
  rex_r = 0x04,
  rex_x = 0x02,
  evex = 0x67
} prefix_encoding;

typedef enum { CHUNK_COUNT, CHUNK_FITTING, ASSEMBLE } ASM_MODE;

// describes how operands are encoded
typedef enum {

  NA = -1,
  MR = 500,
  RM,
  RVM,
  RMV,
  M,
  I,
  O,
  D,
  S
} operand_encoding;

// describes operand layout ex: ri = instruction register, constant
typedef enum {

  opd_error = -1,
  n,
  m,
  r,
  mr,
  rm,
  rr,
  ri,
  mi,
  rrr,
  rri,
  rmi,
  rrm,
  rmr
} operand_format;

// unique identifier for each instuction
typedef enum {

  ASM_ERROR = -1,
  EOI,
  LABEL,
  SKIP,
  adc,
  adcx,
  add,
  adox,
  and,
  bzhi,
  call,
  clc,
  clflush,
  cmova,
  cmovae,
  cmovb,
  cmovbe,
  cmovc,
  cmove,
  cmovg,
  cmovge,
  cmovl,
  cmovle,
  cmovna,
  cmovnae,
  cmovnb,
  cmovnbe,
  cmovnc,
  cmovne,
  cmovng,
  cmovnz,
  cmovo,
  cmovp,
  cmovpe,
  cmovpo,
  cmovs,
  cmovz,
  cmp,
  dec,
  imul,
  inc,
  ja,
  jae,
  jb,
  jbe,
  je,
  jg,
  jge,
  jl,
  jle,
  jmp,
  jne,
  jno,
  jnp,
  jns,
  jo,
  jp,
  jrcxz,
  js,
  lea,
  lfence,
  mfence,
  mov,
  movntdqa,
  movntq,
  movzx,
  mulx,
  nop,
  not,
  or,
  pop,
  push,
  rcr,
  rdtsc,
  ret,
  rorx,
  sar,
  sarx,
  sbb,
  setc,
  seto,
  sfence,
  shl,
  shlx,
  shr,
  shrd,
  shrx,
  sub,
  test,
  xabort,
  xbegin,
  xchg,
  xend,
  xor
} asm_instr;

// used to catagorize instruction based on their functionality
typedef enum {

  DATA_TRANSFER,
  LOGICAL,
  ARITHMETIC,
  SHIFT,
  SHIFT_S,
  BIT,
  CONTROL_FLOW,
  OTHER,
  ASSEMBLYLINE,
} instr_type;

// register bit size and catagory(ext denotes extended x64 registers)
typedef enum {

  reg8 = 0b00000000000,
  ext8 = 0b00010000000,
  noext8 = 0b00100000000,
  reg16 = 0b01000000000,
  ext16 = 0b01010000000,
  reg32 = 0b01100000000,
  ext32 = 0b01110000000,
  reg64 = 0b10000000000,
  ext64 = 0b10010000000,
  mmx64 = 0b10100000000,
} bit_mode;

// register representation (converted from string)
typedef enum {

  reg_error = 0b1000000,
  reg_none = 0b100000,

  // 8bitregisters
  al = 0b00000,
  cl = 0b00001,
  dl = 0b00010,
  bl = 0b00011,
  spl = 0b00100,
  bpl = 0b00101,
  sil = 0b00110,
  dil = 0b00111,

  r8b = 0b01000,
  r9b = 0b01001,
  r10b = 0b01010,
  r11b = 0b01011,
  r12b = 0b01100,
  r13b = 0b01101,
  r14b = 0b01110,
  r15b = 0b01111,

  mm0 = 0b10000,
  mm1 = 0b10001,
  mm2 = 0b10010,
  mm3 = 0b10011,
  mm4 = 0b10100,
  mm5 = 0b10101,
  mm6 = 0b10110,
  mm7 = 0b10111,

} asm_reg;

#endif