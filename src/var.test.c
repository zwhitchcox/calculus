#include <stdio.h>
#include <assert.h>

#include "var.h"

int main() {
  ll_t x = 40ll;
  ll_t y = 40ll;
  // should be 40
  assert(get_lcd(x,y) == 40ll);
  printf("lcd(%lld, %lld): %lld\n", x, y, get_lcd(x, y));
  x = 15ll;
  y = 200ll;
  printf("lcd(%lld, %lld): %lld\n", x, y, get_lcd(x, y));
  assert(get_lcd(x,y) == 600);
  struct PemdasVar *var1 = var_new(x, y);
  struct PemdasVar *var2 = var_new(7ll,40ll);
  var_add(var1, var2);
  // should be 1/4
  var_print(var1);
  // assert(var1->num == 1 && var1->den == 4);
}