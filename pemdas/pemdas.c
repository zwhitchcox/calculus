#include "pemdas.h"
#include "frac.h"

#include <ctype.h>
#include <stdio.h>

struct PemdasToken *new_token() {
  return malloc(sizeof(struct PemdasToken));
}

struct PemdasSubexprToken *new_subexpr_token() {
  return malloc(sizeof(struct PemdasSubexprToken));
}

struct PemdasIntToken *parse_int(char *str, int *len) {
  if (!isdigit(*str)) {
    return NULL;
  }
  int num = 0;

  while (isdigit(*str)) {
    num *= 10;
    num += *str - '0';
    str++;
    (*len)++;
  }

  struct PemdasIntToken *token = (struct PemdasIntToken *)new_token();
  token->data = num;
  token->type = PEMDAS_INT;
  return token;
}

#define NEW_TOKEN_OP(token_type)               \
  token = (struct PemdasOpToken *)new_token(); \
  token->type = PEMDAS_OP;                     \
  token->data = token_type;                    \
  return token;
struct PemdasOpToken *parse_op(char *str, int *len) {
  struct PemdasOpToken *token;
  switch (*str) {
    case '+':
      *len = 1;
      NEW_TOKEN_OP(PEMDAS_ADD);
    case '-':
      *len = 1;
      NEW_TOKEN_OP(PEMDAS_SUB);
    case '/':
      *len = 1;
      NEW_TOKEN_OP(PEMDAS_DIV);
    case '*':
      *len = 1;
      NEW_TOKEN_OP(PEMDAS_MUL);
  }
  return NULL;
}

// https://craftinginterpreters.com/scanning.html
struct PemdasToken *parse(char *str) {
  char *strp = str;
  int parsed = 0;
  struct PemdasToken *cur = new_token();
  struct PemdasToken *dummy = cur;
  cur->type = PEMDAS_DUMMY;
  cur->next = NULL;
  int len = 0;

  while (*strp) {
    len = 0;
    while (isblank(*strp)) {
      strp++;
    }
    if (!((cur->next = (pemdas_token_t *)parse_int(strp, &len)) ||
          (cur->next = (pemdas_token_t *)parse_op(strp, &len)))) {
      fprintf(stderr, "unexpected token at %s", strp);
      return 0;
    }
    cur->next->prev = cur;
    cur = cur->next;
    strp += len;
  }
  cur->next = NULL;
  if (dummy->next) {
    dummy->next->prev = NULL;
  }
  return (struct PemdasToken *)dummy->next;
}