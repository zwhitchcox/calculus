#include "parse.h"

void debug_token_s(struct PemdasToken *token, char *str) {
  int printnl = 1;
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
      printnl = 0;
      debug_token_s(co_token, "");
      break;
    case PEMDAS_INEQ:
      printf(":%s", get_pemdas_ineq_str(((pemdas_ineq_token_t *) token)->data));
      break;
    case PEMDAS_EXPR:
      printf(":expression");
      break;
    default:
      printf("unrecognized type\n");
  }
  if (printnl) {
    printf("\n");
  }
}

void debug_token(struct PemdasToken *token) {
  debug_token_s(token, "debug:");
}
// #include "debug.h"
// #include "string.h"
// #include "stdlib.h"
// #include "stdio.h"

// int count_occurrences(char *str, const char *delim) {
//   int delim_len = strlen(delim);
//   int count = 0;
//   while (*str) {
//     if (!strncmp(str, delim, delim_len)) {
//       count++;
//     }
//     str++;
//   }
//   return count;
// }

// char **split(char *str, const char *del, int *len) {
//   *len = count_occurrences(str, del);
//   char **arr = malloc(sizeof(char*) * (*len));
//   char *token = strtok(str, del);
//   int i = 0;
//   while (token != NULL) {
//     arr[i++] = strdup(token);
//     token = strtok(NULL, del);
//   }
//   return arr;
// }