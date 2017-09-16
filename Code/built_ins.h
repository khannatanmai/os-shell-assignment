#ifndef _BUILT_INS_H_
#define _BUILT_INS_H_

int execute_cd(char *path, char home_dir[]);
int execute_pwd();
int execute_echo(char **tokens, int num);
int execute_pinfo(char *pid);

#endif
