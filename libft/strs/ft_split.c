/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:11:24 by marvin            #+#    #+#             */
/*   Updated: 2024/05/29 03:28:17 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	ft_count_words(char const *s, char c)
{
	int			i;
	int			words;

	i = -1;
	words = 0;
	while (s && s[++i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		words++;
		while (s[i] && s[i] != c)
			i++;
		if (!s[i])
			break ;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		i;
	int		old_i;
	int		j;

	dest = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	i = -1;
	old_i = -1;
	j = -1;
	while (s && s[++i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		old_i = i;
		while (s[i] && s[i] != c)
			i++;
		dest[++j] = ft_strndup((char *)s, old_i, i - old_i);
		if (!s[i])
			break ;
	}
	dest[++j] = NULL;
	return (dest);
}
