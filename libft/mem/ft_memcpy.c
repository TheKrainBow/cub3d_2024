/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 02:16:40 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:28:27 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*bufferdst;
	unsigned char	*buffersrc;

	if (dst == NULL && src == NULL)
		return (NULL);
	bufferdst = (unsigned char *)dst;
	buffersrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		bufferdst[i] = buffersrc[i];
		i++;
	}
	dst = bufferdst;
	return (dst);
}
