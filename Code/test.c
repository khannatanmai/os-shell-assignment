#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

int main()
{
  int x = getppid();

  char s[100];

  sprintf(s,"%d",x);

  printf("--%s--",s);

  return 0;
}
