/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:42:51 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:28:27 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_lists(t_list *lst, int (cmp)(void *))
{
	int	i;

	i = 0;
	while (lst)
	{
		while (lst && cmp(lst->content))
			lst = lst->next;
		if (!lst)
			break ;
		i++;
		while (lst && !cmp(lst->content))
			lst = lst->next;
	}
	return (i);
}

t_list	**ft_lstsplit(t_list *lst, int (*cmp)(void *), void (*del)(void *))
{
	t_list	**dest;
	int		i;

	i = 0;
	dest = ft_calloc(count_lists(lst, cmp) + 1, sizeof(t_list *));
	while (lst)
	{
		while (lst && cmp(lst->content))
		{
			lst = lst->next;
			ft_lstrmone(lst->prev, del);
			lst->prev->next = NULL;
			lst->prev = NULL;
		}
		if (!lst)
			break ;
		dest[i] = lst;
		i++;
		while (lst && !cmp(lst->content))
			lst = lst->next;
	}
	return (dest);
}
