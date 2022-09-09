def_EHelper(ld) {
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 8);
}

def_EHelper(sd) {
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 8);
}

def_EHelper(addi) {
  rtl_addi(s, ddest, id_src1->preg, id_src2->imm);
}

def_EHelper(jal) {
  rtl_li(s, ddest, s->pc + 4);
  rtl_j(s, ((id_src1->imm + s->pc) & 0xffffffffffdfffff));
}

def_EHelper(jalr) {
  rtl_li(s, ddest, s->pc + 4);
  rtl_j(s, ((id_src2->imm + *(id_src1->preg))>>1)<<1);
}
