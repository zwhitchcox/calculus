#include <ctype.h>
#include <stdio.h>

#include "parse.h"
#include "frac.h"

struct PemdasToken *pemdas_new_token() {
  return malloc(sizeof(struct PemdasToken));
}

struct PemdasFracToken *pemdas_new_frac_token(int num, int den) {
  struct PemdasFracToken *token = (struct PemdasFracToken *)pemdas_new_token();
  token->type = PEMDAS_FRAC;
  token->data = frac_new(num, den);
  return token;
}

struct PemdasOpToken *pemdas_new_op_token(enum PemdasOp op) {
  struct PemdasOpToken *token = (struct PemdasOpToken *)pemdas_new_token();
  token->type = PEMDAS_OP;
  token->data = op;
  return token;
}

struct PemdasSubexprToken *pemdas_new_subexpr_token() {
  struct PemdasSubexprToken *token = (struct PemdasSubexprToken *)pemdas_new_token();
  token->type = PEMDAS_SUBEXPR;
  // TODO
  return token;
}

struct PemdasIntToken *pemdas_parse_int(char *str, int *len) {
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

  struct PemdasIntToken *token = (struct PemdasIntToken *)pemdas_new_token();
  token->data = num;
  token->type = PEMDAS_INT;
  return token;
}

struct PemdasOpToken *pemdas_parse_op(char *str, int *len) {
  struct PemdasOpToken *token;
  switch (*str) {
    case '+':
      *len = 1;
      return pemdas_new_op_token(PEMDAS_ADD);
    case '-':
      *len = 1;
      return pemdas_new_op_token(PEMDAS_SUB);
    case '/':
      *len = 1;
      return pemdas_new_op_token(PEMDAS_DIV);
    case '*':
      *len = 1;
      return pemdas_new_op_token(PEMDAS_MUL);
  }
  return NULL;
}

// https://craftinginterpreters.com/scanning.html
struct PemdasToken *pemdas_parse(char *str) {
  char *strp = str;
  int parsed = 0;
  struct PemdasToken *cur = pemdas_new_token();
  struct PemdasToken *dummy = cur;
  cur->type = PEMDAS_DUMMY;
  cur->next = NULL;
  int len = 0;

  while (*strp) {
    len = 0;
    while (isblank(*strp)) {
      strp++;
    }
    if (!((cur->next = (pemdas_token_t *)pemdas_parse_int(strp, &len)) ||
          (cur->next = (pemdas_token_t *)pemdas_parse_op(strp, &len)))) {
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