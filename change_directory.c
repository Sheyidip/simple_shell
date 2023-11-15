#include "shell.h"

/**
 * change_dir - function to change the current working directory
 * @path: the path to the directory to change to
 * Return: 0 for success, 1 for failure
 */
int change_dir(const char *path)
{
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

/**
 * upd_env_var - function to update environment variable after cd
 * @path: the new current working directory path
 * @envp: parent environment
 * Return: 0 for success, 1 for failure
 */
int upd_env_var(const char *path, char *envp[])
{
	if (setenv("OLDPWD", s_getenv("PWD", envp), 1) != 0)
	{
		perror("setenv");
		return (1);
	}

	if (setenv("PWD", path, 1) != 0)
	{
		perror("setenv");
		return (1);
	}

	return (0);
}
/**
 * cd_dir - function to implement cd
 * @args: the flag for cd
 * @envp:parent environment
 * Return: 0 for sucees and 1 otherwise
 */
int cd_dir(const char *args, char *envp[])
{

	if (args == NULL || args[0] == '\0')
	{
		const char *home = s_getenv("HOME", envp);

		if (home == NULL)
		{
			perror("cd");
			return (1);
		}
		args = home;
	}
	else if (s_strcmp(args, "-") == 0)
	{
		const char *prev = s_getenv("OLDPWD", envp);

		if (prev == NULL)
		{
			perror("cd");
			return (1);
		}
		args = prev;
	}

	if (change_dir(args) != 0)
		return (1);
	if (upd_env_var(args, envp) != 0)
		return (1);
	return (0);
}

