/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:04:56 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:28:27 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_tab(char **strs)
{
	ft_print_tab_fd(strs, 1);
}

void	ft_print_tab_fd(char **strs, int fd)
{
	int			i;

	i = -1;
	while (strs && strs[++i])
	{
		ft_putstr_fd(strs[i], fd);
		ft_putchar_fd('\n', fd);
	}
}
