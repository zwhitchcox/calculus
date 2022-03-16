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