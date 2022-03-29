#include "token.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "fraction.h"
#include "common.h"

struct PemdasToken *pemdas_new_token() {
  return malloc(sizeof(struct PemdasToken));
}

struct PemdasFracToken *pemdas_new_frac_token(int num, int den) {
  struct PemdasFracToken *token = (struct PemdasFracToken *)pemdas_new_token();
  token->type = PEMDAS_FRAC;
  token->data = frac_new(num, den);
  return token;
}

struct PemdasVarToken *pemdas_new_var_token(char *name,
                                            struct PemdasToken *coef) {
  struct PemdasVarToken *token = (struct PemdasVarToken *)pemdas_new_token();
  struct PemdasVar *var = malloc(sizeof(struct PemdasVar));
  var->name = name;
  var->coefficient = coef;
  token->type = PEMDAS_VAR;
  token->data = var;
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

struct PemdasIntToken *pemdas_new_int_token(long long data) {
  printf("new int data: %lld\n", data);
  struct PemdasIntToken *token = (struct PemdasIntToken *)pemdas_new_token();
  token->type = PEMDAS_INT;
  token->data = data;
  return token;
}

struct PemdasExprToken *pemdas_new_expr_token(struct PemdasToken *chain) {
  struct PemdasExprToken *token = (struct PemdasExprToken *)pemdas_new_token();
  token->type = PEMDAS_EXPR;
  token->data = chain;
  return token;
}
