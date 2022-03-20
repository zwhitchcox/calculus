#include <stdio.h>
#include <assert.h>
#include "var.h"

int main() {
  int x, y;
  x = 40;
  y = 40;
  // should be 40
  assert(get_lcd(x,y) == 40);
  printf("lcd(%d, %d): %d\n", x, y, get_lcd(x, y));
  x = 15;
  y = 200;
  printf("lcd(%d, %d): %d\n", x, y, get_lcd(x, y));
  assert(get_lcd(x,y) == 600);
  struct PemdasVar *var1 = var_new(x, y);
  struct PemdasVar *var2 = var_new(7,40);
  var_add(var1, var2);
  // should be 1/4
  var_print(var1);
  assert(var1->num == 1 && var1->den == 4);
}