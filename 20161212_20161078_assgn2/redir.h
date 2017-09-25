#ifndef _REDIR_H
#define _REDIR_H

int redir_check(char **tokens, int number_of_tokens);
int redir_input(char **tokens, int number_of_tokens);
int redir_output(char **tokens, int number_of_tokens);
int redir_output_append(char **tokens, int number_of_tokens);
int redir_input_output(char **tokens, int number_of_tokens);

#endif