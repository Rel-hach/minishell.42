/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 15:31:10 by mes-sadk          #+#    #+#             */
/*   Updated: 2022/08/14 22:00:17 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Include/minishell.h"

void	ft_minishell()
{
//	signal_handler();
new_heap(20, 3, APPROVED);
c_delete(3,APPROVED);
//c_delete();

//	ft_call_shell();
}

int	main(int ac, char *av[], char *env[])
{
	(void)env;
	(void)av;
	if (ac == 1)
		ft_minishell();
	else
	 {
	 	opendir(av[1]);
	 	if (!errno)
	 		errno = EISDIR;
	 	ft_err(ft_strdup(av[1]), ERRMSG);
	 	exit (errno);
	}
	return (_RETURN);
}
