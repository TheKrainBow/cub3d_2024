/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:25:31 by krain             #+#    #+#             */
/*   Updated: 2024/04/23 00:20:32 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# define UPPER_HEX_BASE "0123456789ABCDEF"
# define LOWER_HEX_BASE "0123456789abcdef"

void	printf_putchar(char c, int *count);
void	printf_putstr(char *str, int *count);
void	printf_putnbr_hexa(unsigned long int nb, char *base, int *count);
void	printf_putptr(void *ptr, int *count);
void	printf_putnbr(long long int nb, char *base, int len, int *count);

int		ft_printf(const char *str, ...);

#endif
