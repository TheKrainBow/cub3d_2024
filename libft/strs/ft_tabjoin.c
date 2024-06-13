/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 18:36:20 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:28:27 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabjoin(char **s1, char **s2)
{
	char		**dest;
	int			size;
	int			i;

	size = 0;
	i = -1;
	while (s1 && s1[++i])
		size++;
	i = -1;
	while (s2 && s2[++i])
		size++;
	dest = ft_calloc(sizeof(char *), (size + 1));
	size = -1;
	i = -1;
	while (s1 && s1[++i])
		dest[++size] = ft_strdup(s1[i]);
	i = -1;
	while (s2 && s2[++i])
		dest[++size] = ft_strdup(s2[i]);
	return (dest);
}
