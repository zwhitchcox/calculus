# PEDMAS

PEDMAS is an acronym for
  * Parentheses
  * Exponents
  * Multiplication and Division
  * Addition and Subtraction
which is the order of operations when evaluating a algebraic expression.

So if we were to evaluate the expression `3 + 5 * 9`, we would evaluate `5 * 9` first, getting the value `45`. We would then go on to evaluate the addition operation `3 + 45`, which would give us the number `48`.

The precedence of these operations is given by the ordered list of operation types.

This library can evaluate all of these types of algebraic expressions individually and return a string of the new expression.

So, for instance we would evaluate the exponents first while respecting the parentheses. So `8 + 9 * 2^3` would become `8 + 9 * 8`. Next, we would evaluate the multiplication and division so:

`8 + 9 * 8 => 8 + 72`

Finally, we evaluate addition/subtraction, so:

`8 + 72 => 80`

If there were a parenthetical expression within the expression, we would only respect inside the parentheses, so `8 * (3 - 2)` would stay the same for the `MD` evaluation, because the `3 - 2` is located within the parentheses. On the other hand, if there were a multiplicative expression inside the parethenses, that would be evaluated during `MD`, so

`8 * (3 - 2 * 4) => 8 * (3 - 8)`

In addition, if there were a multiplicative expression outside of the parenthetical expression, without the parenthetical expression as an operation, that would still be evaluated, so

`8 * 9 * (3 - 2 * 4) => 72 * (3 - 8)`

Then during the `AD` step, the `(3 - 8)` expression would be evaluated, so

`72 * (3 - 8) => 72 * -5`

This expression can obviously still be simplified, so it may be necessary for an algebraic expression containing a parenthetical expression to be evaluated multiple times, with a loop:

```c
#define MAX_EXPR 10000

int main() {
  char str[MAX_EXPR] = "3 * (9 - 2)";
  char prev_str[MAX_EXPR] = strdup(str);
  do {
    printf("%s", )
  } while (evaluate(str));
}
```

`evaluate` will return the operation performed, which will be automatically detected. So, for instance, if no `MD` is needed, it will skip straight to `AS`. You can detect the operation performed like so:

```c
struct OpType op = evaluate(str);
if (op & SUB) {
  printf("subtraction evaluated");
} else if (op & ADD) {
  printf("addition evaluated");
} else if (op & MUL) {
  printf("multiplication evaluated");
} else if (op & DIV) {
  printf("division evaluated");
} else if (op & EXP) {
  printf("exponent evaluated");
} else {
  printf("expression has been simplified");
}
```

If no operation is necessary, `NULL` will be returned by `evaluate()`.