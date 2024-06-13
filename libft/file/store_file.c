/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:06:05 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/07 01:08:44 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*store_file(int fd)
{
	char			buffer[11];
	int				read_return;
	char			*file_content;

	file_content = NULL;
	read_return = 1;
	while (read_return)
	{
		read_return = read(fd, buffer, 10);
		buffer[read_return] = 0;
		ft_strjoin_to(&file_content, buffer);
	}
	close(fd);
	return (file_content);
}
