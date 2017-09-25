#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include "redir.h"

//int fd=0;

int redir_check(char **tokens, int number_of_tokens)
{
/*	const char* input = "<";
	const char* output = ">";
	const char* outputA = ">>";
*/
	int i;
	int flag = 0;

	for(i=0; i<number_of_tokens; i++)
	{
		if(strcmp(tokens[i],"<")==0)
			flag = 1;			//input from file
		else if(strcmp(tokens[i],">")==0)
		{
			if(flag == 1)
				return 4; //input AND output redir
			else
				return 2; //only output
		}
		else if(strcmp(tokens[i],">>")==0)
			return 3;
	}

	if(flag == 1) //input redir
		return 1;
	else
		return 0;
}

int redir_input(char **tokens, int number_of_tokens)
{
	int fd;
	int i;

	for(i=0; i<number_of_tokens; i++)
		if(strcmp(tokens[i],"<") == 0)
			break;

	char input_file[100];
	strcpy(input_file,tokens[i+1]);

	fd = open(input_file, O_RDONLY);

	if(fd<0)
	{
		perror("Error: Cannot open the input file");
		exit(0);
	}

	tokens[i] = '\0';

	dup2(fd,STDIN_FILENO); //stdin is now this input file
	close(fd);

	execvp(*tokens, tokens);	

	return 0;
}


int redir_output(char **tokens, int number_of_tokens)
{
	int fd;
	int i;

	for(i=0; i<number_of_tokens; i++)
		if(strcmp(tokens[i],">") == 0)
			break;

	char output_file[100];
	strcpy(output_file,tokens[i+1]);

	fd = open(output_file, O_WRONLY | O_CREAT,0644);

	if(fd<0)
	{
		perror("Error: Cannot open the output file");
		exit(0);
	}

	tokens[i] = '\0';

	dup2(fd,STDOUT_FILENO); //stdout is now this output file
	close(fd);

	execvp(*tokens, tokens);	

	return 0;
}

int redir_output_append(char **tokens, int number_of_tokens)
{
	int fd;
	int i;

	for(i=0; i<number_of_tokens; i++)
		if(strcmp(tokens[i],">>") == 0)
			break;

	char output_file[100];
	strcpy(output_file,tokens[i+1]);

	fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND ,0644);

	if(fd<0)
	{
		perror("Error: Cannot open the output file");
		exit(0);
	}

	tokens[i] = '\0';

	dup2(fd,STDOUT_FILENO); //stdout is now this output file
	close(fd);

	execvp(*tokens, tokens);	

	return 0;
}

int redir_input_output(char **tokens, int number_of_tokens)
{
	int fd;
	int i;

	for(i=0; i<number_of_tokens; i++)
		if(strcmp(tokens[i],">") == 0)
			break;

	char output_file[100];
	strcpy(output_file,tokens[i+1]);

	fd = open(output_file, O_WRONLY | O_CREAT,0644);

	if(fd<0)
	{
		perror("Error: Cannot open the output file");
		exit(0);
	}

	tokens[i] = '\0';

	dup2(fd,STDOUT_FILENO); //stdout is now this output file
	close(fd);

	//NOW DO the input redir to the command

	for(i=0; i<number_of_tokens; i++)
		if(strcmp(tokens[i],"<") == 0)
			break;

	char input_file[100];
	strcpy(input_file,tokens[i+1]);

	fd = open(input_file, O_RDONLY);

	if(fd<0)
	{
		perror("Error: Cannot open the input file");
		exit(0);
	}

	tokens[i] = '\0';

	dup2(fd,STDIN_FILENO); //stdin is now this input file
	close(fd);

	execvp(*tokens, tokens);	

	return 0;
}
