#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

/* Typedef structures */
typedef struct {
    char *programName;
    char *inputLine;
    char *commandName;
    int executionCounter;
    int fileDescriptor;
    char **tokens;
    char **environment;
    char **aliasList;
} shellData;

/* Function prototypes */
void handleCtrlC(int unused);
void init_shellData(shellData *data, int argc, char *argv[], char *envp[]);
void runShell(char *prompt, shellData *data);
int executeCommand(shellData *data);
int showEnvironment(shellData *data);
int setEnvironmentVariable(shellData *data);
int unsetEnvironmentVariable(shellData *data);
int searchAndExecuteBuiltins(shellData *data);
int executeExit(shellData *data);
int executeChangeDirectory(shellData *data);
int setWorkingDirectory(shellData *data, char *newDir);
int executeHelpCommand(shellData *data);
int executeManageAliases(shellData *data);
void expandVars(shellData *data);
void expandAlias(shellData *data);
int addBuffer(char *buffer, char *strToAdd);
char *getEnvKey(char *key, shellData *data);
int setEnvKey(char *key, char *value, shellData *data);
int removeEnvKey(char *key, shellData *data);
void printEnviron(shellData *data);
char *_strtok(char *line, char *delim);

#endif /* SHELL_H */

