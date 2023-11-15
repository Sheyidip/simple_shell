#include "shell.h"

static char *token;

static int newString;

static char *tokenStart;

/**
 * s_strchr - function that return pointer to the first occurence of char
 * @string: the string to search
 * @chr: the chracter searching for
 * Return: pointer to the search character
 */
char *s_strchr(const char *string, int chr)
{
	while (*string != '\0')
	{
		if (*string == (char)chr)
			return ((char *)string);
		string++;
	}
	return (NULL);
}

/**
 * initialize_token - function to initialize token process
 * @string: pointer to the null terminated string to tokenize
 * Return: pointer to the initial token position
 */
char *initialize_token(char *string)
{

	if (string != NULL)
	{
		token = string;
		newString = 1;
	}
	else if (token == NULL)
		return (NULL);

	tokenStart = token;

	return (token);
}

/**
 * tokenize - the function tokenize the string using delimeter
 * @token: pointer to the current token position
 * @deli: the delimeter to use
 * Return: pointer to the next token
 */
char *tokenize(char *token, const char *deli)
{

	while (*token != '\0')
	{
		if (s_strchr(deli, *token) != NULL)
		{
			*token = '\0';
			token++;
			if (newString)
			{
				newString = 0;
				return (tokenStart);
			}
		}
		else
			token++;
	}
	return ((newString) ? tokenStart : NULL);
}

/**
 * finalize_token - function that finalize tokenization process and prepare
 * for the next call
 * Return: pointer to the next token if available
 */
char *finalize_token()
{
	if (newString)
	{
		newString = 0;
		return (tokenStart);
	}
	else
	{
		token = NULL;
		return (NULL);
	}
}

/**
 * s_strtok - function that tokenize string base on delimetter
 * @string: the string to tokenize
 * @deli: the delimeter to use
 * Return: pointer to the string tokenize
 */
char *s_strtok(char *string, const char *deli)
{
	char *token = initialize_token(string);

	if (token == NULL)
		return (finalize_token());

	return (tokenize(token, deli));
}
