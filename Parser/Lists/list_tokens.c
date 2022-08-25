/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hach <rel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:46:05 by rel-hach          #+#    #+#             */
/*   Updated: 2022/08/20 15:03:52 by rel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*temp;

	if (lst == NULL)
		return (0);
	size = 0;
	temp = lst;
	while (temp != NULL)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

void	ft_lstadd_back_doubly(t_list **lst, t_list *new)
{
	t_list		*temp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			temp = *lst;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new;
			new->prev = temp;
		}
	}
}

char	*ft_get_type(char *tocken)
{
	if (ft_memcmp(tocken, "|", 2) == 0)
		return ("PIPE");
	if (ft_memcmp(tocken, ">", 2) == 0)
		return ("OUT_RED");
	if (ft_memcmp(tocken, "<", 2) == 0)
		return ("IN_RED");
	if (ft_memcmp(tocken, ">>", 3) == 0)
		return ("APPEND_OUT_RED");
	if (ft_memcmp(tocken, "<<", 3) == 0)
		return ("HEREDOC");
	else
		return ("word");
}

t_list	*ft_new_token(char *last, char *string)
{
	int				i;
	t_list			*new;

	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return (NULL);
	if (ft_strcmp(last, "unset") == 0)
		new->token = string;
	else
		new->token = ft_expand(string);
	new->type = ft_get_type(string);
	new->prev = NULL;
	new->next = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_list	*ft_create_list_for_tockens(char **splitted)
{
	t_list	*head;
	t_list	*new;
	int		i;

	i = 0;
	head = ft_new_token(splitted[i++]);
	while (splitted[i])
	{
		new = ft_new_token(splited[i - 1], splitted[i]);
		ft_lstadd_back_doubly(&head, new);
		i++;
	}
	return (head);
}
