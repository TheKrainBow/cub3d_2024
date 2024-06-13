/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 00:57:57 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:28:17 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strtrunc(char **line, int n)
{
	int		size;
	char	*temp;

	if (!line || !(*line))
		return (0);
	size = ft_strlen(*line);
	if (n > size)
		return (0);
	(*line)[size - n] = 0;
	temp = ft_strdup(*line);
	free(*line);
	*line = temp;
	return (1);
}
