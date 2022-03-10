#include "pemdas.h"

#include "frac.h"

int pemdas_eval_p(struct PemdasToken *token) {

}

int pemdas_eval_e(struct PemdasToken *token) {

}

int pemdas_eval_m(struct PemdasToken *token) {
  int ops_performed;
  if (!token) {
    return 0;
  }
  token = token->next;
  while (token && token->next) {
    if (token->type == PEMDAS_OP
      && token->data == (void *) PEMDAS_MUL
      && token->prev->type == PEMDAS_INT
      && token->next->type == PEMDAS_INT)  {
      token->prev->data = (void *) ((size_t) token->next->data * (size_t) token->prev->data);
      token->prev->next = token->next->next;
      free(token);
      free(token->next);
      ops_performed++;
      token = token->prev;
    }
    token = token->next;
  }
}

int pemdas_eval_d(struct PemdasToken *token) {
  int ops_performed;
  if (!token) {
    return 0;
  }
  token = token->next;

  while (token && token->next) {
    if (!token->type == PEMDAS_DIV) {
      continue;
    }
    if (token->prev->type == PEMDAS_INT) {
      if (token->next->type == PEMDAS_INT) {
        token->prev->type = PEMDAS_FRAC;
        token->prev->data = frac_new((size_t) token->prev->data, (size_t) token->next->data);
        token->prev->next = token->next->next;
        if (token->next->next) {
          token->next->next->prev = token->prev;
        }
        free(token->next);
        void *tmp = token->prev;
        free(token);
        token = tmp;
        frac_reduce(token->data);
      } else if (token->next->type = PEMDAS_FRAC) {
        token->prev->type = PEMDAS_FRAC;
        size_t tmp = (size_t) token->data;
        struct Frac *frac = token->next->data;
        // frac-> += (size_t) token->prev->data * frac->denominator;
        frac_reduce(frac);
      }
    } else if (token->next->type == PEMDAS_FRAC) {

    }
  }
}

int pemdas_eval_a(struct PemdasToken *token) {
  int ops_performed;
  if (!token) {
    return 0;
  }
  token = token->next;
  while (token && token->next) {
    if (token->type == PEMDAS_OP
      && token->data == (void *) PEMDAS_ADD
      && token->prev->type == PEMDAS_INT
      && token->next->type == PEMDAS_INT)  {
      token->prev->data = (void *) ((size_t) token->next->data + (size_t) token->prev->data);
      token->prev->next = token->next->next;
      if (token->next->next) {
        token->next->next->prev = token->prev;
      }
      ops_performed++;
      token = token->prev;
    }
    token = token->next;
  }
}

int pemdas_eval_s(struct PemdasToken *token) {
  int ops_performed;
  if (!token) {
    return 0;
  }
  token = token->next;
  while (token && token->next) {
    if (token->type == PEMDAS_OP
      && token->data == (void *) PEMDAS_SUB
      && token->prev->type == PEMDAS_INT
      && token->next->type == PEMDAS_INT)  {
      token->prev->data = (void *) ((size_t) token->prev->data - (size_t) token->next->data);
      token->prev->next = token->next->next;
      if (token->next->next) {
        token->next->next->prev = token->prev;
      }
      ops_performed++;
      token = token->prev;
    }
    token = token->next;
  }
}

int pemdas_eval(struct PemdasToken *token) {

}