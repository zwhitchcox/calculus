#include "token.h"

#include <stdlib.h>
#include <string.h>

#include "var.h"

struct PedmasToken *pedmas_new_token() {
  return malloc(sizeof(struct PedmasToken));
}

struct PedmasVarToken *pedmas_new_var_token(char *name, ll_t num, ll_t den) {
  struct PedmasVarToken *token = (struct PedmasVarToken *)pedmas_new_token();
  struct PedmasVar *var = malloc(sizeof(struct PedmasVar));
  var->name = name;
  var->num = num;
  var->den = den;
  token->type = PEDMAS_VAR;
  token->data = var;
  return token;
}

struct PedmasOpToken *pedmas_new_op_token(enum PedmasOp op) {
  struct PedmasOpToken *token = (struct PedmasOpToken *)pedmas_new_token();
  token->type = PEDMAS_OP;
  token->data = op;
  return token;
}

struct PedmasIneqToken *pedmas_new_ineq_token(enum PedmasIneq ineq_type) {
  struct PedmasIneqToken *token = (struct PedmasIneqToken *)pedmas_new_token();
  token->type = PEDMAS_INEQ;
  token->data = ineq_type;
  return token;
}


struct PedmasExprToken *pedmas_new_expr_token(struct PedmasToken *chain) {
  struct PedmasExprToken *token = (struct PedmasExprToken *)pedmas_new_token();
  token->type = PEDMAS_EXPR;
  token->data = chain;
  return token;
}
