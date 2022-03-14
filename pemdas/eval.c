#include "eval.h"
#include "print.h"
#include "parse.h"
#include "frac.h"


int (*eval_fns[])(pemdas_token_t*) = {pemdas_eval_p, pemdas_eval_e, pemdas_eval_d, pemdas_eval_m, pemdas_eval_a, pemdas_eval_s};
int eval_fns_len = sizeof(eval_fns) / sizeof(eval_fns[0]);

int pemdas_eval(struct PemdasToken *token) {
  if (token->type == PEMDAS_EXPR) {
    return pemdas_eval_expr(token->data);
  }
}
// evaluate a function, whichever one needs to be evaluated
int pemdas_eval_expr(struct PemdasToken *token) {
  int i = 0;
  int ops_performed = 0;
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
  return 0;
}

int pemdas_eval_p(struct PemdasToken *token) {
  int ops_performed = 0;
  return ops_performed;
}

int pemdas_eval_e(struct PemdasToken *token) {
  return 0;
}

void ensure_frac(struct PemdasToken *token) {
  if (token->type == PEMDAS_FRAC) {
  } else if (token->type == PEMDAS_INT) {
    token->type = PEMDAS_FRAC;
    token->data = frac_new((size_t) token->data, 1);
  } else {
    fprintf(stderr, "can only convert int and frac types to frac\n");
  }
}

int is_num(struct PemdasToken *token) {
  return token->type == PEMDAS_INT || token->type == PEMDAS_FRAC;
}

void simplify_frac(struct PemdasToken *token) {
  if (token->type != PEMDAS_FRAC) {
    fprintf(stderr, "simplify: not frac\n");
    return;
  }
  if (((struct PemdasFracToken *) token)->data->den == 1) {
    token->type = PEMDAS_INT;
    token->data = (void *) (size_t) ((struct PemdasFracToken *) token)->data->num;
    return;
  }
  frac_reduce(token->data);
}


int pemdas_eval_frac_op(struct PemdasToken *token, enum PemdasOp op, void (*fn)(struct Frac *o1, struct Frac *o2)) {
  int ops_performed = 0;
  while (token && token->next) {
    // printf("token type: %s\n", get_pemdas_token_type_str(token->type));
    if (!(token->type == PEMDAS_OP && (enum PemdasOp) token->data == op)) {
      token = token->next;
      continue;
    }
    struct PemdasToken *next = token->next;
    struct PemdasToken *prev = token->prev;
    struct PemdasToken *after = next->next;

    char str[10000];
    if (is_num(prev) && is_num(next)) {
      ensure_frac(prev);
      ensure_frac(next);
      fn(prev->data, next->data);
      free(next);
      prev->next = after;
      if (after) {
        after->prev = prev;
      }
      simplify_frac(prev);
      ops_performed++;
      token = prev;
    } else {
      token = token->next;
    }
  }
  return ops_performed;
}

int pemdas_eval_m(struct PemdasToken *token) {
  return pemdas_eval_frac_op(token, PEMDAS_MUL, frac_mul);
}

int pemdas_eval_d(struct PemdasToken *token) {
  return pemdas_eval_frac_op(token, PEMDAS_DIV, frac_div);
}

int pemdas_eval_a(struct PemdasToken *token) {
  return pemdas_eval_frac_op(token, PEMDAS_ADD, frac_add);
}

int pemdas_eval_s(struct PemdasToken *token) {
  return pemdas_eval_frac_op(token, PEMDAS_SUB, frac_sub);
}