#include<stdio.h>

typedef struct process process;
struct process {
	int pid;
	char pname[100];
	char status; //'R' if Running, 'S' if Stopped
	char bg_fg; //'B' if background, 'F' if foreground
};

process proc_array[1000]; //This array will store all the running processes
int proc_count; //Number of running processes
