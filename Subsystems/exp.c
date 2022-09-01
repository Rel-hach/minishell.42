/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:26:42 by mes-sadk          #+#    #+#             */
/*   Updated: 2022/09/01 12:55:42 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static t_envv	*next_declare(t_envv *env)
{
	t_envv		*temp1;
	t_envv		*temp2;

	temp1 = env;
	temp2 = env;
	while (temp2 && temp2->sort == false)
		temp2 = temp2->next;
	while (temp1 && temp2)
	{
		if (temp1->sort && 0 < ft_strncmp(temp2->name, temp1->name, INT32_MAX))
			temp2 = temp1;
		temp1 = temp1->next;
	}
	if (!temp2 || temp2->sort == false)
		return (NULL);
	return (temp2);
}

static void	write_exp(t_cmd cmd, t_envv	*envv)
{
	write(cmd->out, "declare -x ", 12);
	write(cmd->out, envv->name, ft_strlen(envv->name));
	if (envv->content)
	{
		write(cmd->out, "=\"", 2);
		write(cmd->out, envv->content, ft_strlen(envv->content));
		write(cmd->out, "\"", 1);
	}
	write(cmd->out, "\n", 1);
	envv->sort = false;
}

static void	ex_port(t_cmd cmd)
{
	t_envv	**env;
	t_envv	*envv;

	env = my_env(NULL, _GET);
	envv = next_declare(*env);
	while (envv)
	{
		write_exp(cmd, envv);
		envv = next_declare(*env);
	}
	envv = *env;
	while (envv)
	{
		envv->sort = true;
		envv = envv->next;
	}
	close_fd(cmd->in, cmd->out);
	exit (0);
}

void	export(t_cmd cmd)
{
	int	arg;
	int	c;

	arg = 0;
	stat_loc(0);
	if (!cmd->arv[1])
		return (fork_exec(cmd, ex_port));
	while (cmd->arv[++arg])
	{
		c = -1;
		while (cmd->arv[arg][++c] && (cmd->arv[arg][c] != '=' || !c))
			if (ft_isalpha(cmd->arv[arg][c]) && ft_isdigit(cmd->arv[arg][c])
					&& cmd->arv[arg][c] != '_')
				break ;
		if (ft_isalpha(cmd->arv[arg][0]) && cmd->arv[arg][0] != '_')
			c = 0;
		if (cmd->arv[arg][c] && (cmd->arv[arg][c] != '=' || !c))
			ft_err("msh: export: not a valid identifier", 109);
		else
			set_env(cmd->arv[arg]);
	}
	unset_envv("_");
	cmd->out = 1;
	cmd->in = 0;
}
