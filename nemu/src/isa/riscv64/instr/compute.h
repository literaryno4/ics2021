#include "rtl-basic.h"
def_EHelper(auipc) {
  rtl_li(s, ddest, id_src1->imm + s->pc);
}

//def_EHelper(addi) {
//  rtl_li(s, ddest, id_src1->imm + s->pc);
//}



