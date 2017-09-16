# Operating Systems
## Assignment 2

## Problem Statement: Create a bash-like shell using C

### Team Members:
### Aamir Farhan (20161078)
### Tanmai Khanna (20161212)

## Info about the shell:

- To run the shell, run the command `make` and then `./shell`.
- The shell has a prompt in front of which you can enter your commands.
- There are some **builtin commands** which have been coded into the shell. These are:

	- `echo <string>`: Anything you write after it will be printed onto the shell.
	- `cd`: Any path you enter after this, the shell takes you to that directory. `cd` and `cd ~` take you to the home directory.
	- `pwd`: Gives you the present working directory.
	- `ls`: This command is used to display all the files in the current directory. `ls -l` gives you the list of files along with info about file permissions, author, last modified time, etc. `ls -a` includes hidden files in the display. You can use any combinations of flags, such as `ls -a -l`/`ls -l -a`/`ls -al`/`ls -la`.

- Any other commands you enter, will run as processes if they exist.
- If you put an at the end of your command, (eg. `emacs &` or `gedit&`) it runs the process in the background and the shell continues to take inputs. If you do not include an `&`, the process runs in the foreground and the shell becomes inaccessible until this process closes.

- `pinfo <pid>` gives you information about the process id that you enter in the command. Just `pinfo` gives information about our shell program.

- **Enjoy the Shell! ^_^**


