#include "shell.h"

/**
 * parse_cmd - Parses the command recieved from stdin
 * @input: String gathered from stdin
 * Return: Parsed strings to be used as arguments
 */
char **parse_cmd(char *input)
{
	char **final_arg;
	char *tmp_arg;
	int i;
	int buffsize = BUFSIZE;

	if (input[0] == ' ' && input[_strlen(input)] == ' ')
		exit(0);
	if (input == NULL)
		return (NULL);
	final_arg = malloc(sizeof(char *) * buffsize);
	if (!final_arg)
	{
		free(final_arg);
		perror("hsh");
		return (NULL);
	}
	tmp_arg = _strtok(input, "\n\t\r\a ");
	for (i = 0; tmp_arg; i++)
	{
		final_arg[i] = tmp_arg;
		tmp_arg = _strtok(NULL, "\n\t\r\a ");
	}
	final_arg[i] = NULL;

	return (final_arg);
}
