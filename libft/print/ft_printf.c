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
#define UPPER_HEX_BASE "0123456789ABCDEF"
#define LOWER_HEX_BASE "0123456789abcdef"

void	function_switch(char c, va_list args, int *count)
{
	if (c == 'c')
		printf_putchar(va_arg(args, int), count);
	if (c == 's')
		printf_putstr(va_arg(args, char *), count);
	if (c == 'd' || c == 'i')
		printf_putnbr(va_arg(args, int), "0123456789", 10, count);
	if (c == 'u')
		printf_putnbr(va_arg(args, unsigned int), "0123456789", 10, count);
	if (c == 'x')
		printf_putnbr_hexa(va_arg(args, unsigned int), LOWER_HEX_BASE, count);
	if (c == 'X')
		printf_putnbr_hexa(va_arg(args, unsigned int), UPPER_HEX_BASE, count);
	if (c == 'p')
		printf_putptr(va_arg(args, void *), count);
	if (c == '%')
		printf_putchar('%', count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	va_start(args, str);
	count = 0;
	while (str && *str)
	{
		if (*str == '%')
		{
			str++;
			function_switch(*str, args, &count);
		}
		else
			printf_putchar(*str, &count);
		str++;
	}
	va_end(args);
	return (count);
}
