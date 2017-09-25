#include<stdio.h>
#include<stdlib.h>
#include<env.h>
#include<string.h>

int execute_printenv(char **tokens, int number_of_tokens)
{
	if(number_of_tokens != 2)
	{
		fprintf(stderr,"Error: Invalid number of arguments\n");
		return -1;
	}

	char* val = tokens[1];

	if(tokens[1][0] == '$')
		strcpy(val,&val[1]);

	val = getenv(val);

	printf("%s\n",val);

	return 1;
}

int execute_setenv(char **tokens, int number_of_tokens)
{
	if(number_of_tokens < 2 && number_of_tokens > 3)
	{
		fprintf(stderr, "Error: Invalid number of arguments\n");
		return -1;
	}

	char* var = tokens[1];
	char* val;

	if(number_of_tokens == 3)
		val = tokens[2];
	else
		val = "";

	setenv(var, val, 1);

	return 1;
}

int execute_unsetenv(char **tokens, int number_of_tokens)
{
	if(number_of_tokens != 2)
	{
		fprintf(stderr,"Error: Invalid number of arguments\n");
		return -1;
	}

	char* val = tokens[1];

	unsetenv(val);
	
	return 1;
}