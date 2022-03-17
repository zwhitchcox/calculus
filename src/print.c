#include "print.h"

#include <stdio.h>

#include "debug.h"
#include "var.h"
#include "math.h"
#include "token.h"

int pedmas_sprint_op(char *str, struct PedmasOpToken *op_token) {
  switch (op_token->data) {
    case PEDMAS_ADD:
      return sprintf(str, "+");
    case PEDMAS_SUB:
      return sprintf(str, "-");
    case PEDMAS_MUL:
      return sprintf(str, "*");
    case PEDMAS_DIV:
      return sprintf(str, "/");
    default:
      fprintf(stderr, "unrecognized token %s", str);
      return 0;
  }
}

int pedmas_sprint_var(char *str, struct PedmasVarToken *var_token) {
  char *start = str;
  struct PedmasVar *var = var_token->data;
  int len = 0;
  if (var->num != var->den || !strlen(var->name)) {
    long long num = var->num;
    long long den = var->den;
    if (abs(num) >= abs(den)) {
      long long remainder = num % den;
      long long quotient = num / den;
      if (remainder) {
        str += sprintf(str, "%lld %lld/%lld", quotient, remainder, den);
      } else {
        str += sprintf(str, "%lld", quotient);
      }
    } else {
      str += sprintf(str, "%lld/%lld", num, den);
    }
  }
  str += sprintf(str, "%s", var->name);
  return str - start;
}

int pedmas_sprint_ineq(char *str, struct PedmasIneqToken *ineq_token) {
  switch (ineq_token->data) {
    case PEDMAS_EQ:
      return sprintf(str, "=");
    case PEDMAS_GT:
      return sprintf(str, ">");
    case PEDMAS_GTE:
      return sprintf(str, ">=");
    case PEDMAS_LT:
      return sprintf(str, "<");
    case PEDMAS_LTE:
      return sprintf(str, "<=");
    default:
      fprintf(stderr, "unrecognized token %s", str);
      return 0;
  }
}
int pedmas_sprint_expr(char *str, struct PedmasToken *token) {
  char *start = str;
  while (token) {
    switch (token->type) {
      case PEDMAS_EXPR:
          *str++ = '(';
        str += pedmas_sprint_expr(str, token->data);
          if (*(str - 1) == ' ') {
            *(str - 1) = ')';
            *str++ = ' ';
          } else {
            *str++ = ')';
          }
        break;
      case PEDMAS_OP:
        str += pedmas_sprint_op(str, (struct PedmasOpToken *)token);
        break;
      case PEDMAS_VAR:
        str += pedmas_sprint_var(str, (struct PedmasVarToken *)token);
        break;
      default:
        fprintf(stderr, "pedmas_sprint: Invalid token: %s\n",
                get_pedmas_token_type_str(token->type));
        exit(1);
    }
    if (token->type != PEDMAS_EXPR) {
      *str++ = ' ';
    }
    token = token->next;
  }
  *str = '\0';
  return str - start;
}

int pedmas_sprint(char *str, struct PedmasToken *token) {
  char *start = str;
  while (token) {
    switch (token->type) {
      case PEDMAS_EXPR:
        str += pedmas_sprint_expr(str, token->data);
        break;
      case PEDMAS_INEQ:
        str += pedmas_sprint_ineq(str, (struct PedmasIneqToken *)token);
        break;
      default:
        fprintf(stderr, "pedmas_sprint: Invalid token\n");
        exit(1);
        break;
    }
    if (token->type != PEDMAS_EXPR) {
      *str++ = ' ';
    }
    token = token->next;
  }
  *str = '\0';
  return str - start;
}
