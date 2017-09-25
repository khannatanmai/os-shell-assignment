#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include "run_process.h"
#include "built_ins.h"
#include "ls.h"
#include "env.h"
#include "global.h"
#include "jobs.h"
#include <signal.h>
#include "redir.h"

void sigchld_handler (int sig) {					// function for exiting the background process 
    int status,i,index;
    pid_t child;

    while ((child = waitpid(-1, &status, WNOHANG)) > 0) {
       
        for(i=1; i <= proc_count; i++)
        {
          if(proc_array[i].pid == child)
          {
            index = i;
            delete_job(index);
          }
        }
        printf("\n%s with pid %d exited normally\n",proc_array[index].pname,child);	//Printing the message

    }
}

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
	  else if(redir_check(tokens, number_of_tokens) > 0)
	  	{
	  		int retval = redir_check(tokens, number_of_tokens);

	  		if(retval == 1)
	  			redir_input(tokens, number_of_tokens);
	  		else if(retval == 2)
	  			redir_output(tokens,number_of_tokens);
	  		else if(retval == 3)
	  			redir_output_append(tokens, number_of_tokens);
	  		else
	  			redir_input_output(tokens, number_of_tokens); 	
	  	}
	  else if(strcmp(tokens[0],"pwd") == 0) //implementing pwd
	    {
	      execute_pwd();
	    }
	  else if(strcmp(tokens[0],"echo") == 0) //implementing echo
	    {
	    	if(tokens[1][0] == '$') //printing an environment variable
	    		execute_printenv(tokens, number_of_tokens);
	    	else
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
	  else if(strcmp(tokens[0],"printenv") == 0)
	  	{
	  	  execute_printenv(tokens,number_of_tokens);
	  	}
	  else if(strcmp(tokens[0],"setenv") == 0)
	  	{
	  	  execute_setenv(tokens,number_of_tokens);
	  	}
	  else if(strcmp(tokens[0],"unsetenv") == 0)
	  	{
	  	  execute_unsetenv(tokens,number_of_tokens);
	  	}
	  else if(strcmp(tokens[0],"jobs") == 0)
	  	{
	  	  execute_jobs();
	  	}
	  else if(strcmp(tokens[0],"kjob") == 0)
	  	{
	  	  execute_kjob(tokens,number_of_tokens);
	  	}
	  else if(strcmp(tokens[0],"overkill") == 0)
	  	{
	  	  execute_overkill();
	  	}
	  else if(strcmp(tokens[0],"fg") == 0)
	  	{
	  	  execute_fg(tokens, number_of_tokens);
	  	}
	  else if(execvp(*tokens, tokens) < 0) //all other processes
	    {
	      printf("%s: command not found\n", tokens[0]);
	      exit(1);
	    }
	}
    	else 
		{ 
		  int i;

		  for(i=proc_count; i >= 1; i--)
		  {
		  	proc_array[i+1].pid = proc_array[i].pid;
		  	proc_array[i+1].status = proc_array[i].status;
		  	proc_array[i+1].bg_fg = proc_array[i].bg_fg;
		  	strcpy(proc_array[i+1].pname, proc_array[i].pname);
		  }

		  //adding process to array after pushing all one ahead
		  proc_count++;
		  proc_array[1].pid = pid;
		  proc_array[1].status = 'R';
		  strcpy(proc_array[1].pname, tokens[0]);
		  proc_array[1].bg_fg = 'F';

		  //printf("[%d]\tRunning\t%s[%d]\n",proc_count, proc_array[proc_count].pname, proc_array[proc_count].pid);

		  while(waitpid(-1, &status, 0) != pid)  //Parent process waits for completion  
		    ;

		  printf("%s with pid %d exited normally\n",tokens[0],pid);  

		  //deleting process from array
		  for(i=1; i < proc_count; i++)
		  {
		  	proc_array[i].pid = proc_array[i+1].pid;
		  	proc_array[i].status = proc_array[i+1].status;
		  	proc_array[i].bg_fg = proc_array[i+1].bg_fg;
		  	strcpy(proc_array[i].pname, proc_array[i+1].pname);
		  }

		  proc_count--;
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
		  int i;
	  		
		  for(i=proc_count; i >= 1; i--)
		  {
		  	proc_array[i+1].pid = proc_array[i].pid;
		  	proc_array[i+1].status = proc_array[i].status;
		  	proc_array[i+1].bg_fg = proc_array[i].bg_fg;
		  	strcpy(proc_array[i+1].pname, proc_array[i].pname);
		  }

		  signal(SIGCHLD, sigchld_handler);


		  proc_count++;
		  proc_array[1].pid = pid;
		  proc_array[1].status = 'R';
		  strcpy(proc_array[1].pname, tokens[0]);
		  proc_array[1].bg_fg = 'B';

		  printf("%s\n",proc_array[1].pname);

	 	  return 1;
		}

    }
  
}

  
