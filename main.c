/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 15:31:10 by mes-sadk          #+#    #+#             */
/*   Updated: 2022/08/22 01:25:58 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Include/minishell.h"
#include <sys/stat.h>

void	ft_minishell()
{
	errno = 0;
	ft_call_shell(PRIO_USER);
}

static void	sig()
{
	signal_handler();
}

int	main(int ac, char *av[], char *env[])
{
	sig();
	if (ac == 1)
	{
		env_proc(env, NULL, SAVE);
		ft_minishell();
	}
	else
	{
		opendir(av[1]);
		if (!errno)
			errno = EISDIR;
	 	ft_err(ft_strdup(av[1]));
		exit (errno);
	}
	return (_RETURN);
}
