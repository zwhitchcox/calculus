#include "eval.h"
#include "print.h"
#include "token.h"
#include "var.h"
#include "debug.h"


int (*eval_fns[])(pedmas_token_t*) = {pedmas_eval_p, pedmas_eval_e, pedmas_eval_d, pedmas_eval_m, pedmas_eval_a, pedmas_eval_s};
int eval_fns_len = sizeof(eval_fns) / sizeof(eval_fns[0]);

int pedmas_eval(struct PedmasToken *token) {
  int ops_performed = 0;
  enum PedmasTokenType last;
  while (token) {
    switch (token->type) {
      case PEDMAS_EXPR:
        ops_performed += pedmas_eval_expr(token->data);
        break;
      case PEDMAS_INEQ:
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
int pedmas_eval_expr(struct PedmasToken *token) {
  int ops_performed = 0;
  do {
    int i = 0;
    for (int (*op)(pedmas_token_t*) = eval_fns[i]; i < eval_fns_len; op = eval_fns[++i]) {
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

int pedmas_eval_p(struct PedmasToken *token) {
  int ops_performed = 0;
  while (token) {
    if (token->type == PEDMAS_EXPR) {
      ops_performed += pedmas_eval_expr(token->data);
      // flatten parentheses
      pedmas_token_t *inner_token = ((pedmas_expr_token_t *) token)->data;
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

int pedmas_eval_e(struct PedmasToken *token) {
  return 0;
}

int is_var(struct PedmasVarToken *token) {
  return token->type == PEDMAS_VAR;
}

void simplify_var(struct PedmasVarToken *token) {
  if (token->type != PEDMAS_VAR) {
    fprintf(stderr, "simplify: not var\n");
    return;
  }
  var_reduce(token->data);
}


int pedmas_eval_var_op(struct PedmasToken *token, enum PedmasOp op, void (*fn)(struct PedmasVar *o1, struct PedmasVar *o2)) {
  int ops_performed = 0;
  struct PedmasVarToken *next;
  struct PedmasVarToken *prev;
  struct PedmasToken *after;
  while (token && token->next) {
    if (!(token->type == PEDMAS_OP && (enum PedmasOp) token->data == op)) {
      token = token->next;
      continue;
    }

    char str[10000];

    next = (pedmas_var_token_t *) token->next;
    prev = (pedmas_var_token_t *) token->prev;
    if (is_var(prev) && is_var(next) && !strcmp(next->data->name, prev->data->name)) {
      after = next->next;
      fn(prev->data, next->data);
      free(token);
      prev->next = after;
      if (after) {
        after->prev = (pedmas_token_t *) prev;
      }
      simplify_var(prev);
      ops_performed++;
      token = (pedmas_token_t *) prev;
    }
    token = token->next;
  }

  return ops_performed;
}

int pedmas_eval_m(struct PedmasToken *token) {
  return pedmas_eval_var_op(token, PEDMAS_MUL, var_mul);
}

int pedmas_eval_d(struct PedmasToken *token) {
  return pedmas_eval_var_op(token, PEDMAS_DIV, var_div);
}

int pedmas_eval_a(struct PedmasToken *token) {
  return pedmas_eval_var_op(token, PEDMAS_ADD, var_add);
}

int pedmas_eval_s(struct PedmasToken *token) {
  return pedmas_eval_var_op(token, PEDMAS_SUB, var_sub);
}