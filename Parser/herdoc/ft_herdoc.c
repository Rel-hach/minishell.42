// HEADER 42 ____ USER = rel-hach //

#include "../../Include/minishell.h"

char *heredoc_waiting(int fds[2])
{
	char	*temp;
	int		status;

	close(fds[STDOUT_FILENO]);
	wait(&status);
	stat_loc(status);
	glb_sig(RL_STATE_READCMD);
	if (status !=  0)
		return (NULL);
	glb_sig(_EXECUTE_OK);
	temp = ft_calloc(OPEN_MAX + 1 , 1);
	status = read(fds[STDIN_FILENO], temp, OPEN_MAX);
	if (status < 0)
		return (NULL);
	temp[status] = '\0';
	close(fds[STDIN_FILENO]);
	return (temp);
}

int		quotes_is_there(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_quote(str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*copy_new_delim(char *delim, char *new_delim)
{
	char    c;
    int		i;
    int		j;

    i = 0;
    j = 0;
	while (delim[i])
	{
		if (ft_is_quote(delim[i]))
		{
			c = delim[i];
			while (delim[i] && delim[i] == c)
				i++;
			while (delim[i] && delim[i] != c)
				new_delim[j++] = delim[i++];
			while (delim[i] && delim[i] == c)
				i++;
		}
        else if (!ft_is_quote(delim[i]))
		    new_delim[j++] = delim[i++];
	}
	return (new_delim);
}

char	*ft_rm_quotes(char *delim, int *quote)
{
	int		i;
	int		j;
	char	*new;
    char    c;

	*quote = 1;
	i =	0;
	j = 0;
	while (delim[i])
	{
		if (ft_is_quote(delim[i]))
		{
			c = delim[i];
			while (delim[i] && delim[i] == c)
				i++;
			while (delim[i] && delim[i] != c)
            {
				j++;
                i++;
            }
			while (delim[i] && delim[i] == c)
				i++;
		}
        else if (!ft_is_quote(delim[i]))
        {
            i++;
            j++;
        }
	}
	new = (char *)ft_calloc(sizeof(char), (j + 1));
	if(!new)
		return (NULL);	
    return (copy_new_delim(delim, new));
}

char	*ft_heredoc(char *delim)
{
	char	*line;
	int		fds[2];
	int		quote;

	quote = 0;
	pipe(fds);
	glb_sig(HEREDOC);
	if (fork())
		return (heredoc_waiting(fds));
	signal(SIGINT, SIG_DFL);
	rl_clear_history();
	close(fds[STDIN_FILENO]);
	if (quotes_are_closed(delim))
		exit (1);
	if (quotes_is_there(delim))
		delim = ft_rm_quotes(delim, &quote);
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(delim, line) == 0)
			break ;
		if (quote == 0)
			line = ft_expand_heredoc(line);
		write(fds[STDOUT_FILENO], line, ft_strlen(line));
		write(fds[STDOUT_FILENO], "\n", 1);
		free(line);
	}
	free(line);
	close(fds[STDOUT_FILENO]);
	return (exit(SUCCESS), NULL);
}

char **handel_heredoc(char **str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (ft_strcmp(str[i], "<<") == 0)
		{
			str[i + 1] = ft_heredoc(str[i + 1]);
		}
		i++;
	}
	return (str);
}
