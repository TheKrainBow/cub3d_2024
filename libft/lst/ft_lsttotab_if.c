/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttotab_if.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:51:11 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:28:27 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lsttotab_if(t_list *lst, int (*cmp)(void *), char *(*conv)(void *))
{
	char	**dest;
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (cmp(tmp->content))
			i++;
		tmp = tmp->next;
	}
	dest = ft_calloc(sizeof(char *), (i + 1));
	if (!(dest))
		return (NULL);
	i = 0;
	while (lst)
	{
		if (cmp(lst->content))
			dest[i++] = conv(lst->content);
		lst = lst->next;
	}
	return (dest);
}
