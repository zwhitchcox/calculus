#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "var.h"

#ifndef __PEDMAS_PARSE__
#define __PEDMAS_PARSE__


// parsers
struct PedmasToken *pedmas_parse(char *str);
struct PedmasExprToken *pedmas_parse_expr(char *str, int *len);
struct PedmasExprToken *pedmas_parse_paren(char *str, int *len);
struct PedmasOpToken *pedmas_parse_op(char *str, int *len);
struct PedmasIntToken *pedmas_parse_int(char *str, int *len);
struct PedmasVarToken *pedmas_parse_var(char *str, int *len);
struct PedmasIneqToken *pedmas_parse_Ineq(char *str, int *len);

#endif