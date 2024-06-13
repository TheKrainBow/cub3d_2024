/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_to.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:22:58 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 02:30:28 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strjoin_to(char **dest, char *s2)
{
	char		*temp;

	temp = *dest;
	*dest = ft_strjoin(*dest, s2);
	free(temp);
}
