#include <string.h>

#include "parse.h"
#include "print.h"
#include "eval.h"

#define MAX_STR 10000

void print_chain(char *src, struct PemdasToken *chain) {
  pemdas_sprint(src, chain);
  printf("%s\n", src);
}

void eval_and_print(char *src) {
  char *longer_src = malloc(MAX_STR);
  strcpy(longer_src, src);
  printf("%s\n", longer_src);
  struct PemdasToken *chain = pemdas_parse(longer_src);
  print_chain(longer_src, chain);
  while (pemdas_eval(chain)) {
    print_chain(longer_src, chain);
  }
  printf("\n");
  free(longer_src);
}

// parse ast from string
int main() {
  eval_and_print("1+1+2-3*4");
  eval_and_print("1 / 2 * 3");
  eval_and_print("x = 100 * 3 / 4");
}