#include <string.h>

#include "parse.h"

#define MAX_STR 10000

void print_chain(char *src, struct PemdasToken *chain) {
  pemdas_sprint(src, chain);
  printf("%s\n", src);
}

// parse ast from string
int main() {
  eval_and_print("1 + 1 + 2 - 3 * 4");
  eval_and_print("1 / 2 * 3");
  eval_and_print("x = 100 * 3 / 4");
  eval_and_print("x = 100 / (4 - 2)");
}