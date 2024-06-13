/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrm_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 22:06:14 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:28:27 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrm_if(t_list **lst, int (*cmp)(void *), void (*del)(void*))
{
	t_list	*node;
	t_list	*next;

	node = *lst;
	while (node)
	{
		if (cmp(node->content))
		{
			next = node->next;
			if (node == *lst)
				*lst = next;
			ft_lstrmone(node, del);
			node = next;
		}
		else
			node = node->next;
	}
}
