#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include "built_ins.h"

int execute_cd(char *path, char home_dir[])
{
//  fprintf(stderr,"input:--%s--",path);
  if(path==NULL||path[0]=='~')
  {
    chdir(home_dir);
  }

  else if(chdir(path) < 0)
    {
      printf("%s: Does not exist\n",path);
      return 0;
    }

  return 1;
}

int execute_pwd()
{
  //printf("This is built in\n");
  char cwd[1000];

  getcwd(cwd, sizeof(cwd));
  printf("%s\n",cwd);

  return 1;
}

int execute_echo(char **tokens, int num)
{
  int i;
  
  for(i=1;i<num;i++)
    {
      printf("%s ",tokens[i]);
    }

  printf("\n");

  return 1;
}

int execute_pinfo(char *pid)
{
  int file;
  char process_info[2000];
  char path[1000] = "/proc/";
  
  if(strcmp(pid,"None") == 0)
    {
      char pid_str[20];
      int pid_int = getppid();
      
      sprintf(pid_str,"%d",pid_int);
     
      strcat(path,pid_str);
      strcat(path,"/status");

      //fprintf(stderr,"Path: %s\n",path);

      file = open(path, O_RDONLY);

      read(file, process_info, 2000);

      close(file);
    }
  else //pid given
    {
      strcat(path,pid);
      strcat(path,"/status");

      //fprintf(stderr,"Path: %s\n",path);

      file = open(path, O_RDONLY);

      read(file, process_info, 2000);

      close(file);
    }

  printf("%s", process_info);

  return 1;
}
