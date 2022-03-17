#include "token.h"
#include "debug.h"

void debug_token_o(struct PedmasToken *token, char *str, int nl) {
  printf("%s:%s", str, get_pedmas_token_type_str(token->type));
  switch (token->type) {
    case PEDMAS_OP:
      printf(":%s", get_pedmas_op_str(((pedmas_op_token_t *)token)->data));
      break;
    case PEDMAS_VAR: ;
      struct PedmasVar *var = (struct PedmasVar *) token->data;
      printf(":name->%s,num->%lld,den->%lld", var->name, var->num, var->den);
      break;
    case PEDMAS_INEQ:
      printf(":%s", get_pedmas_ineq_str(((pedmas_ineq_token_t *) token)->data));
      break;
    case PEDMAS_EXPR:;
      printf(":expression");
      pedmas_token_t *cur_token = token->data;
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

void debug_token(char *str, struct PedmasToken *token) {
  debug_token_o(token, str, 1);
}