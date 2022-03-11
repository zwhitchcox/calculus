#include "pemdas.h"
#include "print.h"
#include "eval.h"

#define MAX_STR 10000

void print_chain(char *src, struct PemdasToken *chain) {
  pemdas_sprint(src, chain);
  printf("%s\n", src);
}

// parse ast from string
int main() {
  char src[MAX_STR] = "1 + 1 + 2 - 3 * 4";
  struct PemdasToken *chain = pemdas_parse(src);
  while (pemdas_eval(chain)) {
    print_chain(src, chain);
  }

  char src2[MAX_STR] = "1 / 2 * 3";
  struct PemdasToken *chain2 = pemdas_parse(src2);
  while (pemdas_eval(chain2)) {
    print_chain(src2, chain2);
  }

  // test 2
  // char src2[MAX_STR] = "1 / 2";
  // struct PemdasToken *chain2 = pemdas_parse(src2);
  // print_chain(src2, chain2);
  // pemdas_eval_d(chain2);
  // print_chain(src2, chain2);
  // pemdas_eval_m(chain2);
  // print_chain(src2, chain2);
  // pemdas_eval_a(chain2);
  // print_chain(src2, chain2);
  // pemdas_eval_s(chain2);
  // print_chain(src2, chain2);
}

