#include "my_shell.h"

int searchAndExecuteBuiltins(shellData *data)
{
	int index;
	Builtin builtinsList[] = {
		{"exit", executeExit},
		{"help", executeHelp},
		{"cd", executeCd},
		{"alias", executeAlias},
		{"env", executeEnvironment},
		{"setenv", executeSetEnvironment},
		{"unsetenv", executeUnsetEnvironment},
		{NULL, NULL}
	};

	for (index = 0; builtinsList[index].command != NULL; index++)
	{
		if (compareStrings(builtinsList[index].command, data->commandName, 0))
		{
			return (builtinsList[index].function(data));
		}
	}

	return (-1);
}
