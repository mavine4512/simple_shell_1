#include "shell.h"

/**
 * checks_history - a program function that gets history of files
 * @info: information
 * Return: file history
 */
char *checks_history(info_t *info)
{
	char *buffer, *f;

	f = _getenv(info, "HOME=");

	if (f == NULL)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(f) + _strlen(HIST_FILE) + 2));

	if (buffer == NULL)
	{
		return (NULL);
	}
	buffer[0] = '\0';
	_strcpy(buffer, f);
	_strcati(buffer, "/");
	_strcati(buffer, HIST_FILE);

	return (buffer);
}

/**
 * create_history - a program function tha creates history
 * @info: information
 * Return: history
 */
int create_history(info_t *info)
{
	list_t *node = info->history;
	char *fnname = checks_history(info);
	ssize_t pd;

	if (fnname == NULL)
		return (-1);

	pd = open(fnname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fnname);
	if (pd == -1)
		return (-1);
	while (node != NULL)
	{
		_putsfd(node->str, pd);
		_putfd('\n', pd);
		node = node->next;
	}
	_putfd(BUF_FLUSH, pd);
	close(pd);

	return (1);
}

/**
 * read_history - a program function that reads history
 * @info: information
 * Return: read history
 */
int read_history(info_t *info)
{
	char *buffer = NULL, *fnname = checks_history(info);
	ssize_t kk, drlen, fssize = 0;
	struct stat st;
	int a, end = 0, linecount = 0;

	if (!fnname)
		return (0);

	kk = open(fnname, O_RDONLY);
	free(fnname);
	if (kk == -1)
		return (0);
	if (fssize < 2)
		return (0);
	if (!fstat(kk, &st))
		fssize = st.st_size;

	buffer = malloc(sizeof(char) * (fssize + 1));
	if (!buffer)
		return (0);
	drlen = read(kk, buffer, fssize);
	buffer[fssize] = 0;
	if (drlen <= 0)
		return (free(buffer), 0);
	close(kk);
	for (a = 0; a < fssize; a++)
		if (buffer[a] == '\n')
		{
			buffer[a] = 0;
			list_history(info, buffer + end, linecount++);
			end = a + 1;
		}
	if (end != a)
		list_history(info, buffer + end, linecount++);
	free(buffer);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_idx(&(info->history), 0);
	reassign_history(info);
	return (info->histcount);
}
/**
 * list_history - a program function that lists history file
 * @info: information
 * @buffer: memory location
 * @linenum: line number
 * Return: history list
 */
int list_history(info_t *info, char *buffer, int linenum)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buffer, linenum);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * reassign_history - a program function that assigns history
 * list number
 * @info: information
 * Return: reassigned history number
 */
int reassign_history(info_t *info)
{
	int a = 0;
	list_t *node = info->history;

	for (; node; node = node->next)
	{
		node->num = a++;
	}
	info->histcount = a;
	return (a);
}
