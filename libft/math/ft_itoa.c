/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 23:16:30 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:28:27 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	ft_pow(int a, int b)
{
	int	temp;

	temp = a;
	while (b > 1)
	{
		a *= temp;
		b--;
	}
	if (b == 0)
		return (1);
	return (a);
}

static char	*ft_itoa2(int i, long int n, int neg)
{
	char	*dest;
	int		j;

	j = 0;
	dest = malloc((i + 1) * sizeof(char));
	if (!(dest))
		return (0);
	if (neg == -1)
	{
		dest[0] = '-';
		n *= neg;
		j++;
		i--;
	}
	dest[i] = 0;
	i--;
	while (i >= 0)
	{
		dest[j] = ((n / ft_pow(10, i)) % 10) + '0';
		j++;
		i--;
	}
	dest[j] = 0;
	return (&dest[0]);
}

char	*ft_itoa(int n)
{
	int			i;
	long int	temp;
	int			neg;
	long int	numb;

	temp = n;
	i = 0;
	neg = 1;
	numb = n;
	if (temp < 0)
	{
		i++;
		temp *= -1;
		neg = -1;
	}
	while (temp >= 10)
	{
		i++;
		temp /= 10;
	}
	i++;
	return (ft_itoa2(i, numb, neg));
}
