#ifndef _JOBS_H
#define _JOBS_H

int execute_jobs();
int execute_kjob(char **tokens, int number_of_tokens);
int delete_job(int job_number);
int execute_overkill();
int execute_fg(char **tokens, int number_of_tokens);

#endif