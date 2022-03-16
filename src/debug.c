#include "token.h"
#include "debug.h"

void debug_token_o(struct PemdasToken *token, char *str, int nl) {
  printf("%s:%s", str, get_pemdas_token_type_str(token->type));
  switch (token->type) {
    case PEMDAS_OP:
      printf(":%s", get_pemdas_op_str(((pemdas_op_token_t *)token)->data));
      break;
    case PEMDAS_INT:
      printf(":%ld", (size_t) token->data);
      break;
    case PEMDAS_FRAC:
      printf(":%d/%d", ((pemdas_frac_token_t *)token)->data->num, ((pemdas_frac_token_t *)token)->data->den);
      break;
    case PEMDAS_VAR: ;
      struct PemdasVarToken *var_token = (struct PemdasVarToken *) token;
      struct PemdasToken *co_token = var_token->data->coefficient;
      printf(":%s:val", var_token->data->name);
      debug_token_o(co_token, "", 0);
      break;
    case PEMDAS_INEQ:
      printf(":%s", get_pemdas_ineq_str(((pemdas_ineq_token_t *) token)->data));
      break;
    case PEMDAS_EXPR:;
      printf(":expression");
      pemdas_token_t *cur_token = token->data;
      while (cur_token) {
        debug_token_o(cur_token, "", 0);
        cur_token = cur_token->next;
      }
      break;
    default:
      printf("unrecognized type\n");
  }
  if (nl) {
    printf("\n");
  }

}

void debug_token(char *str, struct PemdasToken *token) {
  debug_token_o(token, str, 1);
}