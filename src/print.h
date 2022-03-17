#ifndef __PEDMAS_PRINT__
#define __PEDMAS_PRINT__

#include "var.h"
#include "token.h"

int pedmas_sprint(char *str, struct PedmasToken *token);
int pedmas_sprint_op(char *str, struct PedmasOpToken *op_token);
int pedmas_sprint_var(char *str, struct PedmasVarToken *var_token);
int pedmas_sprint_num(char *str, struct PedmasToken *num_token);
int pedmas_get_num_len(int num);
#endif