#include "shell.h"

static Alias *alias_list;

/**
 * add_alias - Add a new alias to the list
 * @name: The alias name
 * @value: The alias value
 */

void add_alias(const char *name, const char *value)
{
	Alias *new_alias = malloc(sizeof(Alias));

	if (!new_alias)
	{
		perror("malloc");
		return;
	}
	new_alias->name = strdup(name);
	new_alias->value = strdup(value);
	new_alias->next = alias_list;
	alias_list = new_alias;
}

/**
 * list_aliases - List all defined aliases
 * Return: void
 */
void list_aliases(void)
{
	Alias *current = alias_list;

	while (current != NULL)
	{
		write(STDOUT_FILENO, current->name, strlen(current->name));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, current->value, strlen(current->value));
		write(STDOUT_FILENO, "\n", 1);

		current = current->next;
	}
}

/**
 * find_alias - find an alias by name
 * @name: The alias name to search for
 * Return: Pointer to the found alias or NULL if not found
 */

Alias *find_alias(const char *name)
{
	Alias *current = alias_list;

	while (current)
	{
		if (strcmp(current->name, name) == 0)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

