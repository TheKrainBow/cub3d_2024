/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 02:11:23 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/06 17:04:24 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *p1, const void *p2, size_t n)
{
	const unsigned char	*s1;
	const unsigned char	*s2;
	size_t				i;

	s1 = p1;
	s2 = p2;
	if ((!s1 && !s2) || n == 0)
		return (0);
	if (!s1)
		return (*s2);
	if (!s2)
		return (*s1);
	i = 0;
	while (s1[i] == s2[i] && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}
