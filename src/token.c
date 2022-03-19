#include "token.h"

#include <stdlib.h>
#include <string.h>

#include "frac.h"

struct PemdasToken *pemdas_new_token() {
  return malloc(sizeof(struct PemdasToken));
}

struct PemdasVarToken *pemdas_new_var_token(char *name) {
  struct PemdasVarToken *token = (struct PemdasVarToken *)pemdas_new_token();
  token->type = PEMDAS_VAR;
  token->data = name;
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

struct PemdasExprToken *pemdas_new_expr_token(struct PemdasToken *chain) {
  struct PemdasExprToken *token = (struct PemdasExprToken *)pemdas_new_token();
  token->type = PEMDAS_EXPR;
  token->data = chain;
  return token;
}

/* debugging */
int count_occurrences(char *str, const char *delim) {
  int delim_len = strlen(delim);
  int count = 0;
  while (*str) {
    if (!strncmp(str, delim, delim_len)) {
      count++;
    }
    str++;
  }
  return count;
}

char **split(char *str, const char *del, int *len) {
  *len = count_occurrences(str, del);
  char **arr = malloc(sizeof(char*) * (*len));
  char *token = strtok(str, del);
  int i = 0;
  while (token != NULL) {
    arr[i++] = strdup(token);
    token = strtok(NULL, del);
  }
  return arr;
}
