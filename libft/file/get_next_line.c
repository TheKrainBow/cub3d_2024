/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 00:43:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/11 17:47:23 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	gnl_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	return (len);
}

static char	*gnl_strjoin(const char *s1, const char *s2)
{
	size_t	size;
	char	*result;
	char	*s;

	size = 0;
	if (s1)
		size += gnl_strlen(s1);
	if (s2)
		size += gnl_strlen(s2);
	result = (char *)malloc(sizeof(char) * (size + 1));
	s = result;
	if (s1)
		while (*s1)
			*s++ = *s1++;
	if (s2)
		while (*s2 && *s2 != '\n')
			*s++ = *s2++;
	*s = 0;
	return (result);
}

static int	gnl_strchr(const char *str, char c)
{
	int		pos;

	pos = 0;
	while (str[pos] && str[pos] != c)
		pos++;
	if (str[pos] == c)
		return (pos + 1);
	return (-1);
}

static char	*ft_read(int fd, char *buffer, char *line)
{
	char	*tmp;
	int		read_ret;
	int		pos;

	read_ret = 1;
	while (read_ret > 0)
	{
		read_ret = read(fd, buffer, BUFFER_SIZE);
		if (!line[0] && read_ret <= 0)
			return (free(line), NULL);
		buffer[read_ret] = 0;
		tmp = gnl_strjoin(line, buffer);
		free(line);
		line = tmp;
		pos = gnl_strchr(buffer, '\n');
		if (pos != -1)
		{
			ft_memmove(buffer, buffer + pos, BUFFER_SIZE - pos);
			buffer[BUFFER_SIZE - pos] = 0;
			break ;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char		buffer[100][BUFFER_SIZE + 1];
	int				pos;
	char			*line;

	if (BUFFER_SIZE <= 0 || fd >= 100 || fd < 0)
		return (NULL);
	line = ft_strdup(buffer[fd]);
	if (!line)
		return (NULL);
	if (buffer[fd][0] == '\0')
		return (ft_read(fd, buffer[fd], line));
	pos = gnl_strchr(buffer[fd], '\n');
	if (pos == -1)
		return (ft_read(fd, buffer[fd], line));
	ft_memmove(buffer[fd], buffer[fd] + pos, BUFFER_SIZE - pos);
	return (line);
}
