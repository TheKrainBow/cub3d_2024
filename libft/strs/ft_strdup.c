/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 01:58:13 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:28:27 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*dest;

	size = 0;
	while (s1 && s1[size])
		size++;
	dest = malloc((size + 1) * sizeof(char));
	if (!(dest))
		return (NULL);
	size = 0;
	while (s1 && s1[size])
	{
		dest[size] = s1[size];
		size++;
	}
	dest[size] = 0;
	return (&dest[0]);
}
