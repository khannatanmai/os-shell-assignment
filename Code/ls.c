#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <stdlib.h>
#include "ls.h"

int execute_ls(char **tokens, int number_of_tokens)
{	
  //struct stat fileStat;
  DIR *d;
  struct dirent *dir;
  struct dirent* current_directory;
  struct stat my_stat;
  struct tm lt;  
  struct passwd *pwd;
  d = opendir(".");
  DIR* directory = opendir(".");

  

  if(number_of_tokens == 1) //number of tokens = 1 => it is just 'ls'
    {
      while((dir = readdir(d)) != NULL)
	{
	  if(dir->d_name[0]!='.')
	    {
	      printf("%s 	 ", dir->d_name);		
	    }
	}
      printf("\n");
      closedir(d);
    }

  else if(number_of_tokens == 2 && strcmp(tokens[1],"-a") == 0) //number of tokens = 2 and second token is -a
    {
      while((dir = readdir(d)) != NULL)
	{
	  printf("%s 	 ", dir->d_name);
	}
      printf("\n");
      closedir(d);
    }
  
  else if(number_of_tokens == 2 && strcmp(tokens[1],"-l") == 0) //number of tokens = 2 and second token is -l
    {
      while( (current_directory = readdir(directory) ) )     
	{ 
	  
	  stat(current_directory->d_name, &my_stat);  
	  
	  if ( (stat(current_directory->d_name, &my_stat) ) == 0 )    
	    {

	      pwd = getpwuid(my_stat.st_uid); // Get User-ID
	      
	    }
	  
	  if(current_directory->d_name[0]!='.')
	    {		
	      if (pwd != 0) 
        	{
		  		stat(current_directory->d_name, &my_stat);
    			char time[50];
    			strftime(time, 50, "%Y-%m-%d %H:%M:%S", localtime(&my_stat.st_mtime));
    			
				printf( (S_ISDIR(my_stat.st_mode)) ? "d" : "-");
		  		printf( (my_stat.st_mode & S_IRUSR) ? "r" : "-");
		  		printf( (my_stat.st_mode & S_IWUSR) ? "w" : "-");
		  		printf( (my_stat.st_mode & S_IXUSR) ? "x" : "-");
		  		printf( (my_stat.st_mode & S_IRGRP) ? "r" : "-");
		  		printf( (my_stat.st_mode & S_IWGRP) ? "w" : "-");	//File Permissions
		  		printf( (my_stat.st_mode & S_IXGRP) ? "x" : "-");
		  		printf( (my_stat.st_mode & S_IROTH) ? "r" : "-");
		  		printf( (my_stat.st_mode & S_IWOTH) ? "w" : "-");
		  		printf( (my_stat.st_mode & S_IXOTH) ? "x" : "-");
 
		  		printf(" \t %s \t %ld \t " ,pwd->pw_name, (long)my_stat.st_size);
		  		printf("%s \t",time);
		  		printf("%s", current_directory->d_name);
		  		printf("\n"); 

        	}
	      
	      else  
		{

			stat(current_directory->d_name, &my_stat);
   			char time[50];
   			strftime(time, 50, "%Y-%m-%d %H:%M:%S", localtime(&my_stat.st_mtime));
			
			printf(" \t %s \t %ld \t " ,pwd->pw_name, (long)my_stat.st_size);
		  	printf("%s \t",time);
		  	printf("%s", current_directory->d_name);
		  	printf("\n"); 
		  
		 
		} 
	   }
   	}
      closedir(directory);	
    }

  else if((tokens[1][0]=='-' && tokens[1][1]=='a' && tokens[1][2]=='l') ||
     (tokens[1][0]=='-' && tokens[1][1]=='l' && tokens[1][2]=='a') ||
     (tokens[1][0]=='-' && tokens[1][1]=='a' && tokens[2][0]=='-' && tokens[2][1]=='l') ||
     (tokens[1][0]=='-' && tokens[1][1]=='l' && tokens[2][0]=='-' && tokens[2][1]=='a'))
    {
      while( (current_directory = readdir(directory) ) )     
	{ 

	  stat(current_directory->d_name, &my_stat);  

	  if ( (stat(current_directory->d_name, &my_stat) ) == 0 )    
	    {

	      pwd = getpwuid(my_stat.st_uid); // Get User-ID

	    }
	   		
	  if (pwd != 0) 
	    {
	      		stat(current_directory->d_name, &my_stat);
    			char time[50];
    			strftime(time, 50, "%Y-%m-%d %H:%M:%S", localtime(&my_stat.st_mtime));
    			
				printf( (S_ISDIR(my_stat.st_mode)) ? "d" : "-");
		  		printf( (my_stat.st_mode & S_IRUSR) ? "r" : "-");
		  		printf( (my_stat.st_mode & S_IWUSR) ? "w" : "-");
		  		printf( (my_stat.st_mode & S_IXUSR) ? "x" : "-");
		  		printf( (my_stat.st_mode & S_IRGRP) ? "r" : "-");
		  		printf( (my_stat.st_mode & S_IWGRP) ? "w" : "-");	//File Permissions
		  		printf( (my_stat.st_mode & S_IXGRP) ? "x" : "-");
		  		printf( (my_stat.st_mode & S_IROTH) ? "r" : "-");
		  		printf( (my_stat.st_mode & S_IWOTH) ? "w" : "-");
		  		printf( (my_stat.st_mode & S_IXOTH) ? "x" : "-");
 
		  		printf(" \t %s \t %ld \t " ,pwd->pw_name, (long)my_stat.st_size);
		  		printf("%s \t",time);
		  		printf("%s", current_directory->d_name);
		  		printf("\n"); 
	      
	    }
	  else  
	    {
	      
	      	stat(current_directory->d_name, &my_stat);
   			char time[50];
   			strftime(time, 50, "%Y-%m-%d %H:%M:%S", localtime(&my_stat.st_mtime));
			
			printf(" \t %s \t %ld \t " ,pwd->pw_name, (long)my_stat.st_size);
		  	printf("%s \t",time);
		  	printf("%s", current_directory->d_name);
		  	printf("\n"); 
	    } 
	}
      closedir(directory);			
    }
  

  return 0;
}
