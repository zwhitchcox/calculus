#include <ctype.h>
#include <stdio.h>

#include "parse.h"
#include "frac.h"
#include "string.h"

struct PemdasToken *pemdas_new_token() {
  return malloc(sizeof(struct PemdasToken));
}

struct PemdasFracToken *pemdas_new_frac_token(int num, int den) {
  struct PemdasFracToken *token = (struct PemdasFracToken *)pemdas_new_token();
  token->type = PEMDAS_FRAC;
  token->data = frac_new(num, den);
  return token;
}

struct PemdasVarToken *pemdas_new_var_token(char *str) {
  struct PemdasVarToken *token = (struct PemdasVarToken *)pemdas_new_token();
  token->type = PEMDAS_VAR;
  token->data = str;
  return token;
}

struct PemdasOpToken *pemdas_new_op_token(enum PemdasOp op) {
  struct PemdasOpToken *token = (struct PemdasOpToken *)pemdas_new_token();
  token->type = PEMDAS_OP;
  token->data = op;
  return token;
}

struct PemdasIneqToken *pemdas_new_ineq_token(enum PemdasIneq ineq_type) {
  struct PemdasIneqToken *token = (struct PemdasIneqToken *)pemdas_new_token();
  token->type = PEMDAS_INEQ;
  token->data = ineq_type;
  return token;
}


struct PemdasIntToken *pemdas_new_int_token(int data) {
  struct PemdasIntToken *token = (struct PemdasIntToken *)pemdas_new_token();
  token->type = PEMDAS_INT;
  token->data = data;
  return token;
}

struct PemdasSubexprToken *pemdas_new_subexpr_token(struct PemdasToken *chain) {
  struct PemdasSubexprToken *token = (struct PemdasSubexprToken *)pemdas_new_token();
  token->type = PEMDAS_SUBEXPR;
  token->data = chain;
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
  return pemdas_new_int_token(num);
}

struct PemdasOpToken *pemdas_parse_op(char *str, int *len) {
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

struct PemdasIneqToken *pemdas_parse_ineq(char *str, int *len) {
  switch (*str) {
    case '=':
      *len = 1;
      return pemdas_new_ineq_token(PEMDAS_EQ);
    case '>':
      if (*++str != '=') {
        *len = 1;
        return pemdas_new_ineq_token(PEMDAS_GT);
      }
      *len = 2;
      return pemdas_new_ineq_token(PEMDAS_GTE);
    case '<':
      if (*++str != '=') {
        *len = 1;
        return pemdas_new_ineq_token(PEMDAS_LT);
      }
      *len = 2;
      return pemdas_new_ineq_token(PEMDAS_LTE);
  }
  return NULL;
}

struct PemdasVarToken *pemdas_parse_var(char *str, int *len) {
  if (isalpha(*str)) {
    char *start = str++;
    while (isalnum(*str) || isdigit(*str))
      str++;
    *len = str - start;
    return pemdas_new_var_token(strndup(start, *len));
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
          (cur->next = (pemdas_token_t *)pemdas_parse_op(strp, &len)) ||
          (cur->next = (pemdas_token_t *)pemdas_parse_var(strp, &len)) ||
          (cur->next = (pemdas_token_t *)pemdas_parse_ineq(strp, &len))
    )) {
      fprintf(stderr, "pemdas_parse: unexpected token at %s", strp);
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