//Code to parse input
//Remove spaces, trailing spaces, deal with delimiters

//Arguments: full input string, one array of strings
//Processing: fills up the array of strings with tokens
//Returns: Number of tokens generated

#include <stdio.h>
#include <string.h>
#include "parsing.h"

int parse(char str[],char *args[])
{
	char *arg;
	const char del[2] = " ";
	int count = 0;

	arg = strtok(str, del);

	while( arg != NULL)
	{
		args[count] = arg;
		count++;

		//fprintf(stderr,"token: %s",arg);
		arg = strtok(NULL, del);
	}

return count;
}

/*
int main()
{
	char input[100];
	char *args[100];
	int len;
	gets(input);

	len = parse(input,args);

	int i;

	//printf("\nLOOP\n");
	for(i=0;i<len;i++)
	{
		printf("%s\n",args[i]);
	}

	return 0;
}
*/