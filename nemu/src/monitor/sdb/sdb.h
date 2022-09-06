#ifndef __SDB_H__
#define __SDB_H__

#include <common.h>

word_t expr(char *e, bool *success);

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */
  word_t old_val;
  char expr[1024];

} WP;

WP* wp_head();

void print_watchpoints();

WP* new_wp();

void free_wp(int no);

#endif
