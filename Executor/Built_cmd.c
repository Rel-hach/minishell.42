/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 15:30:32 by mes-sadk          #+#    #+#             */
/*   Updated: 2022/08/01 12:17:46 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../lib/head.h"
# include <head.h>

void    echo(_str put, bool line_opt)
{
    if (line_opt)
        printf("%s",put);
    else
        printf("%s\n",put);
}

t_path  pwd()
{
    char*   pathname;

    pathname = (char *)malloc (PATH_MAX);
    if (!getcwd(pathname, PATH_MAX))
        return (free(pathname), NULL);
    return ((t_path)pathname);/* leak */
}

void    cd(t_path   path)
{
    if (!path || !*path)
        return ;
    if (chdir(path))
        fix_cderr(path);
}

void    b_exit(_head shlvl, int optn)
{
    _ptr crack;

    crack = *shlvl;
    while (*crack + 1)
        crack++;
    if (*crack == '1')
        exit (optn);
    (*crack) -= 1;
}
