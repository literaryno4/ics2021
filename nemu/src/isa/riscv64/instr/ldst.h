#include "common.h"
#include "rtl-basic.h"
#include <rtl/rtl.h>

#ifdef CONFIG_FTRACE 

char* find_symbol(void*);
int space_len = 0;

static void print_space (int len) {
  for (int i = 0; i < len; ++i) {
    printf(" ");
  }
}

#endif

def_EHelper(ld) {
  rtl_lms(s, ddest, dsrc1, id_src2->simm, 8);
}

def_EHelper(lw) {
  rtl_lms(s, ddest, dsrc1, id_src2->simm, 4);
}

def_EHelper(lwu) {
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 4);
}

def_EHelper(lh) {
  rtl_lms(s, ddest, dsrc1, id_src2->simm, 2);
}

def_EHelper(lhu) {
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 2);
}

def_EHelper(lbu) {
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 1);
}

def_EHelper(lb) {
  rtl_lms(s, ddest, dsrc1, id_src2->simm, 1);
}

def_EHelper(sd) {
  rtl_sm(s, ddest, dsrc1, id_src2->simm, 8);
}

def_EHelper(sw) {
  rtl_sm(s, ddest, dsrc1, id_src2->simm, 4);
}

def_EHelper(sh) {
  rtl_sm(s, ddest, dsrc1, id_src2->simm, 2);
}

def_EHelper(sb) {
  rtl_sm(s, ddest, dsrc1, id_src2->simm, 1);
}

def_EHelper(addi) {
  rtl_addi(s, ddest, id_src1->preg, id_src2->simm);
}

def_EHelper(sltiu) {
  rtl_li(s, ddest, ((uint32_t)(*id_src1->preg) < (uint32_t)(id_src2->imm)) ? 1 : 0);
}

def_EHelper(slti) {
  rtl_li(s, ddest, ((int32_t)(*id_src1->preg) < (int32_t)(id_src2->simm)) ? 1 : 0);
}

def_EHelper(andi) {
  rtl_andi(s, ddest, id_src1->preg, id_src2->simm);
}

def_EHelper(xori) {
  rtl_xori(s, ddest, id_src1->preg, id_src2->simm);
}

def_EHelper(ori) {
  rtl_ori(s, ddest, id_src1->preg, id_src2->simm);
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
  rtl_addw(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(subw) {
  rtl_subw(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(mulw) {
  rtl_mulw(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(divw) {
  rtl_divw(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(divuw) {
  rtl_divuw(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(remw) {
  rtl_remw(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(remuw) {
  rtl_remuw(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(add) {
  rtl_add(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(sub) {
  rtl_sub(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(mul) {
  rtl_mulu_lo(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(rem) {
  rtl_divs_r(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(remu) {
  rtl_divu_r(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(div) {
  rtl_divs_q(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(divu) {
  rtl_divu_q(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(sll) {
  rtl_sll(s, ddest, id_src1->preg, id_src2->preg);
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

def_EHelper(xor) {
  rtl_xor(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(or) {
  rtl_or(s, ddest, id_src1->preg, id_src2->preg);
}

// control

def_EHelper(jal) {
  rtl_li(s, ddest, s->pc + 4);
  word_t addr = ((id_src1->imm + s->pc) & 0xffffffffffdfffff);
  rtl_j(s, addr);
#ifdef CONFIG_FTRACE 
  printf("%lx : ", s->pc);
  print_space(space_len);
  printf("call [%s@%lx]\n", find_symbol((void*)addr), addr);
  space_len += 2;
#endif
}

def_EHelper(jalr) {
  rtl_li(s, ddest, s->pc + 4);
  word_t addr = ((id_src2->imm + *(id_src1->preg))>>1)<<1;
  rtl_j(s, addr);
#ifdef CONFIG_FTRACE 
  if (((s->isa.instr.s.rs1) & 0b11110) == 0) {
    space_len -= 2;
    printf("%lx : ", s->pc);
    print_space(space_len);
    printf("ret [%s@%lx]\n", find_symbol((void*)(s->pc + 4)), addr);
  } else {
    printf("%lx : ", s->pc);
    print_space(space_len);
    printf("call [%s@%lx]\n", find_symbol((void*)addr), addr);
    space_len += 2;
  }
#endif
}

// branch
def_EHelper(beq) {
  if ((*id_src1->preg) == (*id_dest->preg)) {
    rtl_j(s,  id_src2->simm + s->pc);
  }
}

def_EHelper(bne) {
  if ((*id_src1->preg) != (*id_dest->preg)) {
    rtl_j(s,  id_src2->simm + s->pc);
  }
}

def_EHelper(blt) {
  if (((int32_t)*id_src1->preg) < ((int32_t)*id_dest->preg)) {
    rtl_j(s,  id_src2->simm + s->pc);
  }
}

def_EHelper(bge) {
  if (((int32_t)*id_src1->preg) >= ((int32_t)*id_dest->preg)) {
    rtl_j(s,  id_src2->simm + s->pc);
  }
}

def_EHelper(bgeu) {
  if (((uint32_t)*id_src1->preg) >= ((uint32_t)*id_dest->preg)) {
    rtl_j(s,  id_src2->imm + s->pc);
  }
}

def_EHelper(bltu) {
  if ((*id_src1->preg) < (*id_dest->preg)) {
    rtl_j(s,  id_src2->imm + s->pc);
  }
}
