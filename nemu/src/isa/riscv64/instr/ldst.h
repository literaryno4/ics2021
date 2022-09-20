#include "rtl-basic.h"
#include <rtl/rtl.h>

def_EHelper(ld) {
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 8);
}

def_EHelper(lw) {
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 4);
}

def_EHelper(lh) {
  rtl_lms(s, ddest, dsrc1, id_src2->imm, 2);
}

def_EHelper(lhu) {
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 2);
}

def_EHelper(lbu) {
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 1);
}

def_EHelper(sd) {
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 8);
}

def_EHelper(sw) {
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 4);
}

def_EHelper(sh) {
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 2);
}

def_EHelper(sb) {
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 1);
}

def_EHelper(addi) {
  rtl_li(s, ddest, (*id_src1->preg + id_src2->simm));
}

def_EHelper(sltiu) {
  rtl_li(s, ddest, ((uint32_t)(*id_src1->preg) < (uint32_t)(id_src2->imm)) ? 1 : 0);
}

def_EHelper(andi) {
  rtl_andi(s, ddest, id_src1->preg, id_src2->simm);
}

def_EHelper(xori) {
  rtl_xori(s, ddest, id_src1->preg, id_src2->simm);
}

// shift

def_EHelper(slli) {
  rtl_slli(s, ddest, id_src1->preg, (id_src2->imm & (0b111111)));
}

def_EHelper(srli) {
  rtl_srli(s, ddest, id_src1->preg, (id_src2->imm & (0b111111)));
}

def_EHelper(srai) {
  rtl_srai(s, ddest, id_src1->preg, (id_src2->imm & (0b111111)));
}

def_EHelper(slliw) {
  rtl_slliw(s, ddest, id_src1->preg, (id_src2->imm & (0b111111)));
}

def_EHelper(srliw) {
  rtl_srliw(s, ddest, id_src1->preg, (id_src2->imm & (0b111111)));
}

def_EHelper(sraiw) {
  rtl_sraiw(s, ddest, id_src1->preg, (id_src2->imm & (0b111111)));
}

def_EHelper(sllw) {
  rtl_sllw(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(srlw) {
  rtl_srlw(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(sraw) {
  rtl_sraw(s, ddest, id_src1->preg, id_src2->preg);
}

// compute

def_EHelper(addiw) {
  rtl_addiw(s, ddest, id_src1->preg, id_src2->imm);
}

def_EHelper(addw) {
  rtl_add(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(subw) {
  rtl_sub(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(mulw) {
  rtl_mulw(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(divw) {
  rtl_divw(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(remw) {
  rtl_remw(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(add) {
  rtl_add(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(sub) {
  rtl_sub(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(mul) {
  rtl_li(s, ddest, ((*id_src1->preg) * (*id_src2->preg)) & 0xffffffff);
}

def_EHelper(slt) {
  if (((int32_t)*id_src1->preg) < ((int32_t)*id_src2->preg)) {
    rtl_li(s, ddest, 1);
  } else {
    rtl_li(s, ddest, 0);
  }
}

def_EHelper(sltu) {
  if ((*id_src1->preg) < (*id_src2->preg)) {
    rtl_li(s, ddest, 1);
  } else {
    rtl_li(s, ddest, 0);
  }
}

def_EHelper(and) {
  rtl_and(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(or) {
  rtl_or(s, ddest, id_src1->preg, id_src2->preg);
}

// control

def_EHelper(jal) {
  rtl_li(s, ddest, s->pc + 4);
  rtl_j(s, ((id_src1->imm + s->pc) & 0xffffffffffdfffff));
}

def_EHelper(jalr) {
  rtl_li(s, ddest, s->pc + 4);
  rtl_j(s, ((id_src2->imm + *(id_src1->preg))>>1)<<1);
}

// branch
def_EHelper(beq) {
  if ((*id_src1->preg) == (*id_dest->preg)) {
    rtl_j(s,  id_src2->imm + s->pc);
  }
}

def_EHelper(bne) {
  if ((*id_src1->preg) != (*id_dest->preg)) {
    rtl_j(s,  id_src2->imm + s->pc);
  }
}

def_EHelper(blt) {
  if (((int32_t)*id_src1->preg) < ((int32_t)*id_dest->preg)) {
    rtl_j(s,  id_src2->imm + s->pc);
  }
}

def_EHelper(bge) {
  if (((int32_t)*id_src1->preg) >= ((int32_t)*id_dest->preg)) {
    rtl_j(s,  id_src2->imm + s->pc);
  }
}

def_EHelper(bltu) {
  if ((*id_src1->preg) < (*id_dest->preg)) {
    rtl_j(s,  id_src2->imm + s->pc);
  }
}
