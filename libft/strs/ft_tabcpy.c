/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:03:51 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:28:27 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabcpy(char **strs)
{
	int			i;
	char		**dest;

	dest = ft_calloc(sizeof(char *), (ft_tablen(strs) + 1));
	i = -1;
	while (strs && strs[++i])
		dest[i] = ft_strdup(strs[i]);
	return (dest);
}
