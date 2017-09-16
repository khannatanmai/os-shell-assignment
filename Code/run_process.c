#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include "run_process.h"
#include "built_ins.h"
#include "ls.h"

int ampersand_check(char **tokens, int num)
{
  //If last token is &, return -1 and remove last token
  if(strcmp(tokens[num-1],"&") == 0)
    {
      tokens[num-1] = 0;
      return -1;
    }
  //If last char of last token is &, return 1 and remove &
  else if(tokens[num-1][strlen(tokens[num-1])-1] == '&') 
    {
      tokens[num-1][strlen(tokens[num-1])-1] = 0;
      return 1;
    }
  else
    return 0;
}
  
int run_process(char **tokens, int number_of_tokens, char home_dir[])
{
  pid_t  pid;
  int    status;

  int flag = 0;

  if(number_of_tokens > 0)
    flag = ampersand_check(tokens,number_of_tokens);
  else
    return 0;

  if(flag == -1) //& is a separate token and num_of_tokens needs to be reduced by 1
    number_of_tokens--;

  if(flag == 0) //FOREGROUND PROCESS
    {
      if ((pid = fork()) < 0) //Fork a child
	{     
	  printf("Error while forking a child process\n");
	  exit(1);
	}
      else if (pid == 0) //Execute new process in the child process
	{
	  if(strcmp(tokens[0],"cd") == 0) //implementing cd
	    {
	      execute_cd(tokens[1],home_dir);
	    }
	  else if(strcmp(tokens[0],"pwd") == 0) //implementing pwd
	    {
	      execute_pwd();
	    }
	  else if(strcmp(tokens[0],"echo") == 0) //implementing echo
	    {
	      execute_echo(tokens,number_of_tokens);
	    }
	  else if(strcmp(tokens[0],"pinfo") == 0) //implement pinfo
	    {
	      if(number_of_tokens == 1)
		execute_pinfo("None");
	      else
		execute_pinfo(tokens[1]);
		
	    }
	  else if(strcmp(tokens[0],"ls") == 0)
	    {
	      execute_ls(tokens,number_of_tokens);
	    }
	  else if(execvp(*tokens, tokens) < 0) //all other processes
	    {
	      printf("%s: command not found\n", tokens[0]);
	      exit(1);
	    }
	}
      else //Parent process waits for completion
	{                                  
	  while(waitpid(-1, &status, 0) != pid)    
	    ;
	}
    }
  else //BACKGROUND PROCESS
    {
      if ((pid = fork()) < 0) //Fork a child
	{     
	  printf("Error while forking a child process\n");
	  exit(1);
	}
      else if (pid == 0) //Execute new process in the child process
	{
	  if(strcmp(tokens[0],"ls") == 0)
	    {
	      execute_ls(tokens,number_of_tokens);
	    }
	  else if(execvp(*tokens, tokens) < 0) //all other processes
	    {
	      printf("%s: command not found\n", tokens[0]);
	      exit(1);
	    }
	}
      else //Parent does not wait for completion of child process
	{
	  return 1;
	}

    }
  
}

  
