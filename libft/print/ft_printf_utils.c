/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:37:26 by maagosti          #+#    #+#             */
/*   Updated: 2024/04/30 05:03:09 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printf_putchar(char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	printf_putstr(char *str, int *count)
{
	if (!str)
		printf_putstr("(null)", count);
	while (str && *str)
	{
		printf_putchar(*str, count);
		str++;
	}
}

void	printf_putnbr_hexa(unsigned long int nb, char *base, int *count)
{
	if (nb >= 16)
		printf_putnbr_hexa(nb / 16, base, count);
	printf_putchar(base[nb % 16], count);
}

void	printf_putptr(void *ptr, int *count)
{
	long int	n;

	n = (long int)ptr;
	if (ptr == NULL)
	{
		printf_putstr("(nil)", count);
		return ;
	}
	printf_putstr("0x", count);
	printf_putnbr_hexa(n, LOWER_HEX_BASE, count);
}

void	printf_putnbr(long long int nb, char *base, int len, int *count)
{
	if (nb < 0)
	{
		nb = -nb;
		printf_putchar('-', count);
	}
	if (nb >= len)
		printf_putnbr(nb / len, base, len, count);
	printf_putchar(base[nb % len], count);
}
