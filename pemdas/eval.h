#include "parse.h"

#ifndef __PEMDAS_EVAL__
#define __PEMDAS_EVAL__
int pemdas_eval(struct PemdasToken *token);
int pemdas_eval_p(struct PemdasToken *token);
int pemdas_eval_e(struct PemdasToken *token);
int pemdas_eval_m(struct PemdasToken *token);
int pemdas_eval_d(struct PemdasToken *token);
int pemdas_eval_a(struct PemdasToken *token);
int pemdas_eval_s(struct PemdasToken *token);
#endif