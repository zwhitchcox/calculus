#include <stdlib.h>

#ifndef __PEMDAS_VAR__
#define __PEMDAS_VAR__

#include "token.h"
#include "common.h"


typedef struct PemdasVar {
  char *name;
  ll_t num;
  ll_t den;
  struct PemdasVar *pow;
} pemdas_var_t;

struct PemdasVar *var_new(ll_t num, ll_t den);
ll_t get_gcd(ll_t x, ll_t y);
ll_t get_lcd(ll_t x, ll_t y);
void var_denominate(struct PemdasVar *var, ll_t den);
void var_reduce(struct PemdasVar *var);
void var_print(struct PemdasVar *var);
void var_add(struct PemdasVar *x, struct PemdasVar *y);
void var_div(struct PemdasVar *x, struct PemdasVar *y);
void var_sub(struct PemdasVar *x, struct PemdasVar *y);
void var_mul(struct PemdasVar *x, struct PemdasVar *y);

#endif /* __PEMDAS_VAR__ */