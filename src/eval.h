#include "parse.h"

#ifndef __PEDMAS_EVAL__
#define __PEDMAS_EVAL__
int pedmas_eval(struct PedmasToken *token);
int pedmas_eval_expr(struct PedmasToken *token);
int pedmas_eval_p(struct PedmasToken *token);
int pedmas_eval_e(struct PedmasToken *token);
int pedmas_eval_m(struct PedmasToken *token);
int pedmas_eval_d(struct PedmasToken *token);
int pedmas_eval_a(struct PedmasToken *token);
int pedmas_eval_s(struct PedmasToken *token);
#endif