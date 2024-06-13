/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 02:27:30 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:28:27 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*bufferdst;
	unsigned char	*buffersrc;

	bufferdst = (unsigned char *)dst;
	buffersrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		bufferdst[i] = buffersrc[i];
		if (bufferdst[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
