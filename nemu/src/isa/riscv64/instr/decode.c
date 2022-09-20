#include "../local-include/reg.h"
#include <cpu/ifetch.h>
#include <isa-all-instr.h>

def_all_THelper();

static uint32_t get_instr(Decode *s) {
  return s->isa.instr.val;
}
// decode operand helper
#define def_DopHelper(name) \
  void concat(decode_op_, name) (Decode *s, Operand *op, word_t val, bool flag)

static inline def_DopHelper(i) {
  op->imm = val;
}

static inline def_DopHelper(r) {
  bool is_write = flag;
  static word_t zero_null = 0;
  op->preg = (is_write && val == 0) ? &zero_null : &gpr(val);
}

static inline def_DHelper(I) {
  decode_op_r(s, id_src1, s->isa.instr.i.rs1, false);
  decode_op_i(s, id_src2, (sword_t)s->isa.instr.i.simm11_0, false);
  decode_op_r(s, id_dest, s->isa.instr.i.rd, true);
}

static inline def_DHelper(U) {
  decode_op_i(s, id_src1, (sword_t)s->isa.instr.u.simm31_12 << 12, true);
  decode_op_r(s, id_dest, s->isa.instr.u.rd, true);
}

static inline def_DHelper(S) {
  decode_op_r(s, id_src1, s->isa.instr.s.rs1, false);
  sword_t simm = (s->isa.instr.s.simm11_5 << 5) | s->isa.instr.s.imm4_0;
  decode_op_i(s, id_src2, simm, false);
  decode_op_r(s, id_dest, s->isa.instr.s.rs2, false);
}

static inline def_DHelper(B) {
  decode_op_r(s, id_src1, s->isa.instr.s.rs1, false);
  sword_t simm = ((s->isa.instr.b.simm12 << 12) | (s->isa.instr.b.imm11 << 11) | 
                  (s->isa.instr.b.imm10_5 << 5) | (s->isa.instr.b.imm4_1 << 1));
  decode_op_i(s, id_src2, simm, false);
  decode_op_r(s, id_dest, s->isa.instr.s.rs2, false);
}

static inline def_DHelper(R) {
  decode_op_r(s, id_src1, s->isa.instr.r.rs1, false);
  decode_op_r(s, id_src2, s->isa.instr.r.rs2, false);
  decode_op_r(s, id_dest, s->isa.instr.r.rd, false);
}

static inline def_DHelper(J) {
  sword_t simm = ((sword_t)s->isa.instr.j.simm20 << 20) | ((sword_t )s->isa.instr.j.imm19_12 << 12) |
                 ((sword_t)s->isa.instr.j.imm11 << 11) | ((sword_t )s->isa.instr.j.imm10_1 << 1);
  decode_op_i(s, id_src1, simm, true);
  decode_op_r(s, id_dest, s->isa.instr.j.rd, true);
}

def_THelper(load) {
  def_INSTR_TAB("??????? ????? ????? 011 ????? ????? ??", ld);
  def_INSTR_TAB("??????? ????? ????? 001 ????? ????? ??", lh);
  def_INSTR_TAB("??????? ????? ????? 101 ????? ????? ??", lhu);
  def_INSTR_TAB("??????? ????? ????? 010 ????? ????? ??", lw);
  def_INSTR_TAB("??????? ????? ????? 100 ????? ????? ??", lbu);
  return EXEC_ID_inv;
}

def_THelper(store) {
  def_INSTR_TAB("??????? ????? ????? 011 ????? ????? ??", sd);
  def_INSTR_TAB("??????? ????? ????? 000 ????? ????? ??", sb);
  def_INSTR_TAB("??????? ????? ????? 001 ????? ????? ??", sh);
  def_INSTR_TAB("??????? ????? ????? 010 ????? ????? ??", sw);
  return EXEC_ID_inv;
}

def_THelper(branch) {
  def_INSTR_TAB("??????? ????? ????? 000 ????? ????? ??", beq);
  def_INSTR_TAB("??????? ????? ????? 001 ????? ????? ??", bne);
  def_INSTR_TAB("??????? ????? ????? 100 ????? ????? ??", blt);
  def_INSTR_TAB("??????? ????? ????? 110 ????? ????? ??", bltu);
  def_INSTR_TAB("??????? ????? ????? 101 ????? ????? ??", bge);
  return EXEC_ID_inv;
}

def_THelper(computeI) {
  def_INSTR_TAB("??????? ????? ????? 000 ????? ????? ??", addi);
  def_INSTR_TAB("000000? ????? ????? 001 ????? ????? ??", slli);
  def_INSTR_TAB("000000? ????? ????? 101 ????? ????? ??", srli);
  def_INSTR_TAB("010000? ????? ????? 101 ????? ????? ??", srai);
  def_INSTR_TAB("??????? ????? ????? 011 ????? ????? ??", sltiu);
  def_INSTR_TAB("??????? ????? ????? 111 ????? ????? ??", andi);
  def_INSTR_TAB("??????? ????? ????? 100 ????? ????? ??", xori);
  return EXEC_ID_inv;
}

def_THelper(computeIW) {
  def_INSTR_TAB("??????? ????? ????? 000 ????? ????? ??", addiw);
  def_INSTR_TAB("0000000 ????? ????? 001 ????? 00110 11", slliw);
  def_INSTR_TAB("0000000 ????? ????? 101 ????? 00110 11", srliw);
  def_INSTR_TAB("0100000 ????? ????? 101 ????? 00110 11", sraiw);

  return EXEC_ID_inv;
}

def_THelper(computeR) {
  def_INSTR_TAB("0000000 ????? ????? 000 ????? ????? ??", add);
  def_INSTR_TAB("0100000 ????? ????? 000 ????? ????? ??", sub);
  def_INSTR_TAB("0000000 ????? ????? 010 ????? ????? ??", slt);
  def_INSTR_TAB("0000000 ????? ????? 011 ????? ????? ??", sltu);
  def_INSTR_TAB("0000000 ????? ????? 111 ????? ????? ??", and);
  def_INSTR_TAB("0000001 ????? ????? 000 ????? ????? ??", mul);
  def_INSTR_TAB("0000000 ????? ????? 110 ????? ????? ??", or);
  return EXEC_ID_inv;
}

def_THelper(computeRW) { 
  def_INSTR_TAB("0000000 ????? ????? 000 ????? ????? ??", addw); 
  def_INSTR_TAB("0100000 ????? ????? 000 ????? ????? ??", subw);
  def_INSTR_TAB("0000001 ????? ????? 000 ????? ????? ??", mulw);
  def_INSTR_TAB("0000001 ????? ????? 100 ????? ????? ??", divw);
  def_INSTR_TAB("0000001 ????? ????? 110 ????? ????? ??", remw);
  def_INSTR_TAB("0000000 ????? ????? 001 ????? ????? ??", sllw);
  def_INSTR_TAB("0000000 ????? ????? 101 ????? ????? ??", srlw);
  def_INSTR_TAB("0100000 ????? ????? 101 ????? ????? ??", sraw);
  return EXEC_ID_inv;
}

def_THelper(jump) {
  def_INSTR_TAB("??????? ????? ????? 000 ????? ????? ??", jalr);
  return EXEC_ID_inv;
}

def_THelper(main) {
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 00000 11", I     , load);
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 01000 11", S     , store);
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 00101 11", U     , auipc);

  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 01101 11", U     , lui);

  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 11000 11", B     , branch);

  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 00100 11", I     , computeI);

  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 00110 11", I     , computeIW);

  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 01100 11", R     , computeR);

  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 01110 11", R     , computeRW);

  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 11001 11", I     , jump);
  
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 11011 11", J     , jal);

  def_INSTR_TAB  ("??????? ????? ????? ??? ????? 11010 11",         nemu_trap);

  return table_inv(s);
};

int isa_fetch_decode(Decode *s) {
  s->isa.instr.val = instr_fetch(&s->snpc, 4);
  int idx = table_main(s);
  return idx;
}
