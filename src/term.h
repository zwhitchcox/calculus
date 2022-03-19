#include <stdlib.h>

#ifndef __PEMDAS_VAR__
#define __PEMDAS_VAR__

#include "common.h"

typedef struct PemdasVar {
  char letter;
  int exp;
  struct PemdasVar *next;
} pemdas_var_t;

typedef struct PemdasCoef {
  ll_t num;
  ll_t den;
} pemdas_coef_t;

typedef struct PemdasTerm {
  struct PemdasVar *var;
  struct PemdasCoef *coef;
} pemdas_term_t;

struct PemdasTerm *term_new(ll_t num, ll_t den);
ll_t get_gcd(ll_t x, ll_t y);
ll_t get_lcd(ll_t x, ll_t y);
void pemdas_term_denominate(struct PemdasTerm *term, ll_t den);
void pemdas_term_reduce(struct PemdasTerm *term);
void pemdas_term_print(struct PemdasTerm *term);
void pemdas_term_add(struct PemdasTerm *x, struct PemdasTerm *y);
void pemdas_term_div(struct PemdasTerm *x, struct PemdasTerm *y);
void pemdas_term_sub(struct PemdasTerm *x, struct PemdasTerm *y);
void pemdas_term_mul(struct PemdasTerm *x, struct PemdasTerm *y);

#endif /* __PEMDAS_VAR__ */