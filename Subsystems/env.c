/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:34:19 by mes-sadk          #+#    #+#             */
/*   Updated: 2022/08/28 00:45:33 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

t_envv	**my_env(t_envv **env, t_req ord)
{
	static t_envv	**envr;
	t_envv			*mng;

	if (ord == SAVE)
		envr = env;
	if (ord == _SET && envr)
	{
		while (*envr)
		{
			mng = *envr;
			free((void *)mng->content);
			free((void *)mng->name);
			*envr = mng->next;
			free((void *)mng);
		}
		free((void *)envr);
		return (NULL);
	}
	env = envr;
	return (env);
}

char	**env_to_argv(t_envv **env)
{
	t_envv	*mng;
	int		size;
	char	**argv;

	size = 0;
	mng	= *env;
	while (size++, mng)
		mng = mng->next;
	mng = *env;
	argv = (t_head) malloc(sizeof(argv) * size);
	argv[--size] = NULL;
	while (mng)
	{
		argv[--size] = ft_strjoin(mng->name, "=");
		argv[size] = ft_strjoin(argv[size], mng->content);
		mng = mng->next;
	}
	return (argv);
}

void	env(t_cmd cmd)
{
	t_envv	**env;
	t_envv	*envv;

	env = my_env(NULL, _GET);
	envv = *env;
	while (envv)
	{
		if (envv->content)
		{
			write(cmd->out, envv->name, ft_strlen(envv->name));
			write(cmd->out, "=", 2);
			write(cmd->out, envv->content, ft_strlen(envv->content));
			write(cmd->out, "\n", 2);
		}
		envv = envv->next;
	}
	write(cmd->out,"_=/usr/bin/env\n", 16);
	close_fd(cmd->in, cmd->out);
	cmd->out = 1;
	cmd->in = 0;
}

void	*get_env(t_str var)
{
	t_envv	**env;
	t_envv	*envv;

	if (ft_strncmp(var, "?", 2) == SUCCESS)
		return (ft_itoa(stat_loc(-42)));
	env = my_env(NULL, _GET);
	envv = *env;
	while (envv->next)
	{
		if (ft_strncmp(envv->name, var, INT32_MAX) == SUCCESS)
			return ((void *)envv->content);
		envv = envv->next;
	}
	return ("");
}