#include <stdio.h>
#include "pemdas.h"
#include "pemdas.print.h"

int pemdas_sprint_op(char *str, struct PemdasOpToken *op_token) {
  switch (op_token->data) {
    case PEMDAS_ADD:
      return sprintf(str, " + ");
    case PEMDAS_SUB:
      return sprintf(str, " - ");
    case PEMDAS_MUL:
      return sprintf(str, " * ");
    case PEMDAS_DIV:
      return sprintf(str, " / ");
    default:
      fprintf(stderr, "unrecognized token %s", str);
      return 0;
  }
}

int pemdas_sprint_int(char *str, struct PemdasIntToken *op_token) {
  return sprintf(str, "%d", op_token->data);
}

int pemdas_sprint_var(char *str, struct PemdasVarToken *var_token) {
  return sprintf(str, " %s ", var_token->data);
}

int pemdas_sprint(char *str, struct PemdasToken *token) {
  char *start = str;
  while (token) {
    switch (token->type) {
      case PEMDAS_SUBEXPR:
        str += pemdas_sprint(str, token->data);
        break;
      case PEMDAS_OP:
        str += pemdas_sprint_op(str, (struct PemdasOpToken *) token);
        break;
      case PEMDAS_INT:
        str += pemdas_sprint_int(str, (struct PemdasIntToken *) token);
        break;
      case PEMDAS_VAR:
        str += pemdas_sprint_var(str, (struct PemdasVarToken *) token);
        break;
      default:
        fprintf(stderr, "Invalid token\n");
    }
    token = token->next;
  }
  return str - start;
}
