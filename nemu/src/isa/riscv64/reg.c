#include <isa.h>
#include "local-include/reg.h"
#include <stdbool.h>

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

#define NR_REGS 32

void isa_reg_display() {
  printf("register info: \n");
  int i; 
  for (i = 0; i < NR_REGS; ++i) {
    printf("%4s %16p\n", regs[i], (void *)cpu.gpr[i]._64);
  }
  printf("%4s %16p\n", "pc", (void *)cpu.pc);
}

word_t isa_reg_str2val(const char *s, bool *success) {
  int i; 
  for (i = 0; i < NR_REGS; ++i) {
    if (strcmp(s, regs[i]) == 0) {
      *success = true;
      return cpu.gpr[i]._64;
    }
  }
  *success = false;
  return 0;
}
