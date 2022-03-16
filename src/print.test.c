#include <stdio.h>

#include "pemdas.h"
#include "frac.h"
#include "print.h"


int main() {
  struct Frac *frac = frac_new(1,4);
  struct PemdasFracToken *frac_token = (struct PemdasFracToken *) new_token();
  frac_token->data = frac;
  char s[1000];
  s[pemdas_sprint_frac(s, frac_token)] = '\0';
  printf("Should be 1/4: %s\n", s);
  frac_token->data->num = 8;
  s[pemdas_sprint_frac(s, frac_token)] = '\0';
  printf("Should be 2: %s\n", s);
}