#include <stdlib.h>   
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipe.h"


int pipe(char **tokens, int num)
{
  char arg1[100][100], arg2[100][100];
  int i,j;
  
  for(i=0;i<num;i++)
  {
    if(tokens[i]=="|")
      break;
  }

  for(j=0;j<i;j++)
  {
    strcpy(arg1[j],tokens[j]);
  }

  int count = 0;
  for(j=i+1;j<num;j++)
  {
    strcpy(arg2[count],tokens[j]);
    count++;
  }


  int fds[2];
  pipe(fds);

  int i;
  pid_t pid = fork();

  if (pid == -1) 
  {     //error
        printf("error fork!!\n");
        return 1;
  }

  if (pid == 0) 
  { // child process
        
        close(fds[1]);
        dup2(fds[0], 0);
        //close(fds[0]);
        execvp(arg2[0], arg2); // run command AFTER pipe character in user
        char *error = strerror(errno);
        //printf("unknown command\n");
        return 0;
  }

  else { // parent process
        close(fds[0]);
        dup2(fds[1], 1);
        //close(fds[1]);
        execvp(arg1[0], arg1); // run command BEFORE pipe character in userinput
        char *error = strerror(errno);
        printf("unknown command\n");
        return 0;
    } 

}