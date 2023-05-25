#include "shell.h"

/**
 * main - a function that runs a UNIX command program
 * @argc: Argument count supplied to the program
 * @argv: Argument vector of array of pointers
 *
 * Return: Returns condition
 */
int main(__attribute__((unused)) int argc, char **argv)
{
	char *input_data, **cmd, **commands;
	int count = 0, i, condition = 1, stat = 0;

	if (argv[1] != NULL)
	{
		read_file(argv[1], argv);
	}
	signal(SIGINT, signal_to_handle);
	while (condition)
	{
		count++;
		if (isatty(STDIN_FILENO))
		{
			prompt();
		}
		input_data = _getline();
		if (input_data[0] == '\0')
		{
			continue;
		}
		history(input_data);
		commands = separator(input_data);
		for (i = 0; commands[i] != NULL; i++)
		{
			cmd = parse_cmd(commands[i]);
			if (_strcmp(cmd[0], "exit") == 0)
			{
				free(commands);
				exit_bul(cmd, input_data, argv, count, stat);
			}
			else if (check_builtin(cmd) == 0)
			{
				stat = handle_builtin(cmd, stat);
				free(cmd);
				continue;
			}
			else
				stat = check_cmd(cmd, input_data, count, argv);
			free(cmd);
		}
		free(input_data);
		free(commands);
		wait(&stat);
	}
	return (stat);
}

