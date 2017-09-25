#ifndef _ENV_H
#define _ENV_H

int execute_printenv(char **tokens, int number_of_tokens);
int execute_setenv(char **tokens, int number_of_tokens);
int execute_unsetenv(char **tokens, int number_of_tokens);

#endif
