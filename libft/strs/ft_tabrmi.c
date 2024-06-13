/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabrmi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 17:02:19 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:28:27 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_tabrmi(char **strs, int index)
{
	char	**new_strs;
	int		i;
	int		j;
	int		size;

	size = ft_tablen(strs);
	new_strs = ft_calloc(size, sizeof(char *));
	if (!(new_strs) || index < 0 || index > size)
		return (NULL);
	i = -1;
	j = 0;
	while (strs[++i])
	{
		if (i == index)
			j++;
		else
			new_strs[i - j] = ft_strdup(strs[i]);
	}
	new_strs[i - j] = NULL;
	return (new_strs);
}
