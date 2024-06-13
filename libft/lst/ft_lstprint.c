/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:51:14 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:28:27 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint_fd(t_list *lst, int fd)
{
	int		i;

	i = 0;
	while (lst)
	{
		ft_putchar_fd('|', fd);
		ft_putstr_fd((char *)lst->content, fd);
		ft_putstr_fd("|\n", fd);
		lst = lst->next;
		i++;
	}
}

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		printf("|%s|\n", (char *)lst->content);
		lst = lst->next;
	}
}
