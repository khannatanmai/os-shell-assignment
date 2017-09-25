#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include "global.h"
#include "jobs.h"

int delete_job(int job_number)
{
	int i;

	for(i = job_number; i < proc_count; i++)
	{
	  	proc_array[i].pid = proc_array[i+1].pid;
	  	proc_array[i].status = proc_array[i+1].status;
	  	proc_array[i].bg_fg = proc_array[i+1].bg_fg;
	  	strcpy(proc_array[i].pname, proc_array[i+1].pname);
	}

	proc_count--;
}

int execute_jobs()
{
	int i;

	for(i=1;i <= proc_count; i++)
	{
		if(proc_array[i].status == 'R')
			printf("[%d]\tRunning\t%s[%d]\n",i, proc_array[i].pname, proc_array[i].pid);
		else
			printf("[%d]\tStopped\t%s[%d]\n",i, proc_array[i].pname, proc_array[i].pid);		
	}

	return 1;
}

int execute_kjob(char **tokens, int number_of_tokens)
{
	if(number_of_tokens != 3)
	{
		fprintf(stderr,"Error: Invalid number of arguments\n");
		return -1;
	}

	int job_no = atoi(tokens[1]);
	int sig = atoi(tokens[2]);

	int pid = proc_array[job_no].pid;

	int retval = kill(pid, sig);

	if(sig == 9)
		delete_job(job_no);

	return retval;
}

int execute_overkill()
{
	int i;

	for(i=1; i <= proc_count; i++)
	{
		kill(proc_array[i].pid,9);
		delete_job(i);
	}

	return 1;
}

int execute_fg(char **tokens, int number_of_tokens)
{
	int i;

	if(number_of_tokens != 2)
		fprintf(stderr, "Error: Invalid number of arguments\n"); 

	int job_no = atoi(tokens[1]);

	if(job_no <= proc_count)
	{
		int pid = proc_array[job_no].pid;

		kill(pid, SIGCONT);
		waitpid(-1,&i,0);
	}
	else
		fprintf(stderr, "Error: Invalid Job Number\n");

	return 1;
}