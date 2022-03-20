#include <stdlib.h>

#ifndef __PEDMAS_VAR__
#define __PEDMAS_VAR__

#include "token.h"
#include "common.h"


typedef struct PedmasVar {
  char *name;
  ll_t num;
  ll_t den;
  struct PemdasVar *pow;
} pedmas_var_t;

struct PedmasVar *var_new(ll_t num, ll_t den);
ll_t get_gcd(ll_t x, ll_t y);
ll_t get_lcd(ll_t x, ll_t y);
void var_denominate(struct PedmasVar *var, ll_t den);
void var_reduce(struct PedmasVar *var);
void var_print(struct PedmasVar *var);
void var_add(struct PedmasVar *x, struct PedmasVar *y);
void var_div(struct PedmasVar *x, struct PedmasVar *y);
void var_sub(struct PedmasVar *x, struct PedmasVar *y);
void var_mul(struct PedmasVar *x, struct PedmasVar *y);

#endif /* __PEDMAS_VAR__ */