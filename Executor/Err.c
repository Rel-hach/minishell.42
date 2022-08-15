/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 07:36:20 by mes-sadk          #+#    #+#             */
/*   Updated: 2022/08/13 22:06:10 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Include/minishell.h"

void ft_err(t_str err_msg, t_req msg)
{
    if (errno <= 0 || errno >= sys_nerr) /*  Known errors (errno) : sys_nerr 0 -> 106 */
        return ;
    if (msg == ERRMSG)
    {
        perror(err_msg); /* <err_msg>: Undefined error: 0 */
        free((char *)err_msg);
    }
    else
    {
        printf("%s\n", strerror(errno));
    }
}