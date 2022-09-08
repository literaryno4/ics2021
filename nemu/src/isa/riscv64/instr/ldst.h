def_EHelper(ld) {
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 8);
}

def_EHelper(sd) {
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 8);
}

def_EHelper(addi) {
  printf(ASNI_BG_RED "executing li..." ASNI_NONE "\n");
  // rtl_li(s, ddest, id_src1->imm);
  rtl_addi(s, ddest, id_src1->preg, id_src2->imm);
}

def_EHelper(jal) {
  printf(ASNI_BG_RED "executing jal... to %lx" ASNI_NONE "\n", id_src1->imm);
  // ra <- pc + 4
  rtl_li(s, ddest, s->pc + 4);
  rtl_j(s, ((id_src1->imm + s->pc) & 0xffffffffffdfffff));
}

def_EHelper(jalr) {
  printf(ASNI_BG_RED "executing jalr... to %lx" ASNI_NONE "\n", (id_src2->imm + s->pc) & (0xfffffffffffffffe));
  // ra <- pc + 4
  rtl_li(s, ddest, s->pc + 4);
  // rtl_addi(s, id_src1->preg, id_src1->preg, id_src2->imm);
  rtl_j(s, (id_src2->imm + s->pc) & (0xfffffffffffffffe));
}
