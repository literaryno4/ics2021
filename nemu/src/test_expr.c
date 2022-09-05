#include <common.h>

#include "./monitor/sdb/sdb.h"
#include <stdio.h>
#include <stdlib.h>

void test_expr() {
  FILE* stream;
  char* line = NULL;
  size_t len = 0;
  ssize_t nread;
  word_t result;
  char* exp;
  bool success;

  if ((stream = fopen("/home/chao/ics2021/nemu/src/input", "r")) == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  while ((nread = getline(&line, &len, stream)) != -1) {
    result = atoi(strtok(line, " "));
    exp = strtok(NULL, "\n");
    printf("%d %s: ", result, exp);
    word_t ans = expr(exp, &success)
    if (result == ans) {
      printf("pass\n");
    } else {
      printf("failed, %ld\n", ans);
    }
  }

  free(line);
  fclose(stream);
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  test_expr();
  return 0;
}
