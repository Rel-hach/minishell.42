/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_from_wr_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:38:16 by mes-sadk          #+#    #+#             */
/*   Updated: 2022/09/05 12:46:31 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static void	hd_out_of(t_cmd mngr, t_cmd cmd)
{
	int		fd[2];

	if (!mngr)
	{
		perror("PARSER ERROR <->\n");
		ft_exit(33);
	}
	close_fd(&(cmd->in), NULL);
	pipe(fd);
	cmd->in = fd[STDIN_FILENO];
	write(fd[STDOUT_FILENO], mngr->token, ft_strlen(mngr->token));
	close(fd[STDOUT_FILENO]);
	mngr->symbol = 'F';
}

static void	rd_out_of(t_cmd mngr, t_cmd cmd)
{
	if (!mngr)
	{
		perror("PARSER ERROR <->\n");
		ft_exit(33);
	}
	close_fd(&(cmd->in), NULL);
	cmd->in = open(mngr->token, O_RDONLY);
	ft_err(mngr->token, errno);
	mngr->symbol = 'F';
}

static void	insert_doc(t_cmd mngr, t_cmd cmd)
{
	if (!mngr)
	{
		perror("PARSER ERROR <->\n");
		ft_exit(33);
	}
	close_fd(NULL, &(cmd->out));
	cmd->out = open(mngr->token, O_WRONLY
			| O_CREAT | O_APPEND, 0644);
	ft_err(mngr->token, errno);
	mngr->symbol = 'F';
}

static void	insert_file(t_cmd mngr, t_cmd cmd)
{
	if (!mngr)
	{
		perror("PARSER ERROR <->\n");
		ft_exit(33);
	}
	close_fd(NULL, &(cmd->out));
	cmd->out = open(mngr->token, O_WRONLY
			| O_TRUNC | O_CREAT, 0644);
	ft_err(mngr->token, errno);
	mngr->symbol = 'F';
}

void	rf_wi(t_cmd cmd)
{
	t_cmd	mngr;

	mngr = cmd;
	cmd->arc = 0;
	while (mngr)
	{
		if (mngr->symbol == HEREDOC)
			hd_out_of(mngr->next, cmd);
		else if (mngr->symbol == '<')
			rd_out_of(mngr->next, cmd);
		else if (mngr->symbol == O_APPEND)
			insert_doc(mngr->next, cmd);
		else if (mngr->symbol == '>')
			insert_file(mngr->next, cmd);
		else if (mngr->symbol == 'w')
			cmd->arc++;
		mngr = mngr->next;
	}
}
