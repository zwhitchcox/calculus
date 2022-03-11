#include "pemdas.h"

#ifndef __PEMDAS_PRINT__
#define __PEMDAS_PRINT__
int pemdas_sprint(char *str, struct PemdasToken *token);
int pemdas_sprint_op(char *str, struct PemdasOpToken *op_token);
int pemdas_sprint_int(char *str, struct PemdasIntToken *op_token);
int pemdas_sprint_var(char *str, struct PemdasVarToken *var_token);
int pemdas_sprint_frac(char *str, struct PemdasFracToken *frac_token);
int pemdas_sprint_num(char *str, struct PemdasToken *num_token);
int pemdas_get_num_len(int num);
#endif