#include<stdio.h>
#include<sys/utsname.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include "parsing.h"
#include "run_process.h"

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
  char cwd[1009];
  char command[200];
  
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
	printf("<%s@%s:~$>",buffer.nodename,buffer.sysname);
      else if(strlen(cwd)>strlen(home_dir))
	{
	  printf("<%s@%s:~",buffer.nodename,buffer.sysname);
	  print_dir(cwd,home_dir);
	}
      else
	{
	  printf("<%s@%s:%s$>",buffer.nodename,buffer.sysname,cwd);
	}
     
      fgets(command, sizeof(command), stdin);
	  command[strcspn(command, "\n")] = '\0';      
      number_of_tokens = parse(command, tokens);
	    
      //print(tokens,number_of_tokens);
      
      run_process(tokens, number_of_tokens, home_dir); //running the first token as a process
    }
  
  return 0;
}
