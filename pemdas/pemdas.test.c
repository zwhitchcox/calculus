#include "pemdas.h"
#include "print.h"
#include "eval.h"

#define MAX_STR 10000

// parse ast from string
int main() {
  char src[MAX_STR] = "1 + 1 + 2 - 3 * 4";
  struct PemdasToken *chain = parse(src);
  pemdas_sprint(src, chain);
  printf("%s\n", src);
  pemdas_eval_m(chain);
  pemdas_sprint(src, chain);
  printf("%s\n", src);
  pemdas_eval_a(chain);
  pemdas_sprint(src, chain);
  printf("%s\n", src);
  pemdas_eval_s(chain);
  pemdas_sprint(src, chain);
  printf("%s\n", src);

  // test 2
  char src2[MAX_STR] = "1 / 2";
}

