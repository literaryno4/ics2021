#include <cpu/decode.h>
#include "../local-include/rtl.h"

#define INSTR_LIST(f) f(auipc) f(ld) f(sd) f(inv) f(nemu_trap) \
        f(addi) f(jal) f(jalr) f(lw) f(addw) f(add) f(sub) f(sltiu) \
        f(beq) f(bne) f(addiw) f(sw) f(lui) f(mulw) f(divw) f(remw) \
        f(slli) f(srli) f(srai) f(lbu) f(subw) f(sb) f(slliw) f(srliw) \
        f(sraiw) f(blt) f(slt) f(andi) f(sh) f(sllw) f(and) f(sltu) f(xori) \
        f(or) f(bge)

def_all_EXEC_ID();
