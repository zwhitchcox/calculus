#include "eval.h"
#include "print.h"
#include "token.h"
#include "var.h"
#include "debug.h"


int (*eval_fns[])(pemdas_token_t*) = {pemdas_eval_p, pemdas_eval_e, pemdas_eval_d, pemdas_eval_m, pemdas_eval_a, pemdas_eval_s};
int eval_fns_len = sizeof(eval_fns) / sizeof(eval_fns[0]);

int pemdas_eval(struct PemdasToken *token) {
  int ops_performed = 0;
  enum PemdasTokenType last;
  while (token) {
    switch (token->type) {
      case PEMDAS_EXPR:
        ops_performed += pemdas_eval_expr(token->data);
        break;
      case PEMDAS_INEQ:
        // TODO
        break;
      default:
        break;
    }
    token = token->next;
  }
  return ops_performed;
}

// evaluate a function, whichever one needs to be evaluated
int pemdas_eval_expr(struct PemdasToken *token) {
  int ops_performed = 0;
  do {
    int i = 0;
    for (int (*op)(pemdas_token_t*) = eval_fns[i]; i < eval_fns_len; op = eval_fns[++i]) {
      int cur_ops_performed = 0;
      while (cur_ops_performed = op(token)) {
        ops_performed += cur_ops_performed;
        cur_ops_performed = 0;
      }
      if (ops_performed) {
        return ops_performed;
      }
    }
  } while (token = token->next);
  return ops_performed;
}

int pemdas_eval_p(struct PemdasToken *token) {
  int ops_performed = 0;
  while (token) {
    if (token->type == PEMDAS_EXPR) {
      ops_performed += pemdas_eval_expr(token->data);
      // flatten parentheses
      pemdas_token_t *inner_token = ((pemdas_expr_token_t *) token)->data;
      if (!inner_token->next) {
        token->type = inner_token->type;
        token->data = inner_token->data;
        free(inner_token);
      }
    }
    token = token->next;
  }
  return ops_performed;
}

int pemdas_eval_e(struct PemdasToken *token) {
  return 0;
}

int is_var(struct PemdasToken *token) {
  return token->type == PEMDAS_VAR;
}

void simplify_var(struct PemdasVarToken *token) {
  if (token->type != PEMDAS_VAR) {
    fprintf(stderr, "simplify: not var\n");
    return;
  }
  var_reduce(token->data);
}


int pemdas_eval_var_op(struct PemdasToken *token, enum PemdasOp op, void (*fn)(struct PemdasVar *o1, struct PemdasVar *o2)) {
  int ops_performed = 0;
  while (token && token->next) {
    if (!(token->type == PEMDAS_OP && (enum PemdasOp) token->data == op)) {
      token = token->next;
      continue;
    }

    char str[10000];

    if (is_var(token->prev) && is_var(token->next)) {
      struct PemdasVarToken *next = (pemdas_var_token_t *) token->next;
      struct PemdasVarToken *prev = (pemdas_var_token_t *) token->prev;
      struct PemdasToken *after = next->next;
      fn(prev->data, next->data);
      free(token);
      prev->next = after;
      if (after) {
        after->prev = (pemdas_token_t *) prev;
      }
      simplify_var(prev);
      ops_performed++;
      token = (pemdas_token_t *) prev;
    } else {
      token = token->next;
    }
  }

  return ops_performed;
}

int pemdas_eval_m(struct PemdasToken *token) {
  return pemdas_eval_var_op(token, PEMDAS_MUL, var_mul);
}

int pemdas_eval_d(struct PemdasToken *token) {
  return pemdas_eval_var_op(token, PEMDAS_DIV, var_div);
}

int pemdas_eval_a(struct PemdasToken *token) {
  return pemdas_eval_var_op(token, PEMDAS_ADD, var_add);
}

int pemdas_eval_s(struct PemdasToken *token) {
  return pemdas_eval_var_op(token, PEMDAS_SUB, var_sub);
}