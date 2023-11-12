#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 
#include <stddef.h>
#include <fcntl.h>
#include <errno.h> 
#include <sys/types.h>
#include <sys/wait.h> 
#include <sys/stat.h> 
#include <signal.h>
#include <errno.h> 

typedef struct info
{
	char *programName;
	char *inputLine;
	char *commandName;
	int executionCounter;
	int fileDescriptor;
	char **tokens;
	char **envinronment;
	char **aliasList;
} shellData;


void handleCtrlC(int unused);

void init_shellData(shellData *data, int argc, char *argv[], char *envp[])

void runShell(char *prompt, shellData *data);

int executeCommand(shellData *data);

#endif
