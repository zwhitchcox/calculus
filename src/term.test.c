#include <stdio.h>
#include <assert.h>
#include "var.h"
#include "common.h"

int add_vars_no_poly() {
  return 0;
}

int add_vars() {
  struct PemdasVar *var1 = pemdas_var_new(15ll, 200ll);
  struct PemdasVar *var2 = pemdas_var_new(7ll,40ll);
  pemdas_var_add(var1, var2);
  return 1;
}

#define test(fn) printf(#fn "\n");assert(fn());

int main() {
  int x, y;
  x = 40;
  y = 40;

  // should be 40


  test(add_vars)
  // assert(get_lcd(x,y) == 40);
  // printf("lcd(%lld, %lld): %lld\n", x, y, get_lcd(x, y));
  // x = 15;
  // y = 200;
  // printf("lcd(%lld, %lld): %lld\n", x, y, get_lcd(x, y));
  // assert(get_lcd(x,y) == 600);
  // struct PemdasVar *var1 = pemdas_var_new(x, y);
  // struct PemdasVar *var2 = pemdas_var_new(7,40);
  // pemdas_var_add(var1, var2);
  // // should be 1/4
  // pemdas_var_print(var1);
  // assert(var1->num == 1 && var1->den == 4);
}