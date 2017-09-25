#include<stdio.h>
#include<sys/utsname.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include "parsing.h"
#include "run_process.h"
#include "global.h"
#include "redir.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void sigintHandler(int sig_num)
{
	signal(SIGINT, sigintHandler);
	fflush(stdout);
}

void print(char* hello[], int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		printf("Token #%d: %s\n",i,hello[i]);
	}
}

void print_dir(char arr[],char brr[])
{
	int len = strlen(brr);
	  	int i,j;
	  	for(i=0;i<len;i++)
	  	{
	  		if(arr[i]!=brr[i])
	  			break;
	  	}

	  	for(j=i;j<strlen(arr);j++)
	    {
	    	printf("%c",arr[j]);
	    }
	    printf("/$>");
}
struct utsname buffer;

int main()
{
	int proc_count = 0;
	  char cwd[1009];
  char command[200];
  
  int x = setpgid(0,0);
  char home_dir[1000];
  getcwd(home_dir,sizeof(home_dir));
  
  char *tokens[100];
  int number_of_tokens;
  
  if (uname(&buffer) != 0)
    {
      perror("uname");
      exit(EXIT_FAILURE);
    }
  

  while(1)
    {
      memset(tokens, 0, sizeof tokens); //Empty Tokens array
      
      getcwd(cwd,sizeof(cwd));
      
      if(strcmp(cwd,home_dir) == 0)
      {
      	printf(ANSI_COLOR_YELLOW);
      	printf("<%s@%s:~$>",buffer.nodename,buffer.sysname);
      	printf(ANSI_COLOR_RESET);
      }
		
      else if(strlen(cwd)>strlen(home_dir))
	{
	  printf(ANSI_COLOR_YELLOW);
	  printf("<%s@%s:~",buffer.nodename,buffer.sysname);
	  printf(ANSI_COLOR_CYAN);
	  print_dir(cwd,home_dir);
	  printf(ANSI_COLOR_RESET);
	}
      else
	{
	  printf(ANSI_COLOR_YELLOW);
	  printf("<%s@%s:",buffer.nodename,buffer.sysname);
	  printf(ANSI_COLOR_CYAN);
	  printf("%s",cwd);
	  printf(ANSI_COLOR_YELLOW);
	  printf("$>");
	  printf(ANSI_COLOR_RESET);
	}
     
      fgets(command, sizeof(command), stdin);

      signal(SIGINT, sigintHandler);				// for CTRL+C

	  command[strcspn(command, "\n")] = '\0';      
      number_of_tokens = parse(command, tokens);
	    
      //print(tokens,number_of_tokens);
		
	  //QUIT SHELL
	  if(number_of_tokens == 1)
	  	if(strcmp(tokens[0],"quit") == 0)
	  		{
	  			kill(0,SIGINT);
	  			kill(0,SIGKILL);
	  		}

    run_process(tokens, number_of_tokens, home_dir); //running the first token as a process
    }
  
  return 0;
}
