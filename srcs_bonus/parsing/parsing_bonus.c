/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:49:26 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/01 19:01:11 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_lsttotab(t_list *lst, int len)
{
	char	**dest;
	int		i;
	int		src_len;

	dest = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!(dest))
		return (NULL);
	i = 0;
	while (lst)
	{
		dest[i] = ft_calloc(sizeof(char *), len + 1);
		src_len = ft_strlen(lst->content);
		ft_memcpy(dest[i], lst->content, src_len);
		ft_memset(dest[i] + src_len, ' ', len - src_len);
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

int	line_error(char *line, char *error)
{
	ft_putstr_fd("Error in input file:\n> '", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("'\n> ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	return (ERROR);
}

int	parse_line(t_data *data, char *line)
{
	int	i;

	if (data->parsing.is_map)
		return (parse_map_line(data, line));
	i = 0;
	while (line[i] && ft_iswhitespace(line[i]))
		i++;
	if (!line[i])
		return (0);
	if ((line[i] == 'F' || line[i] == 'C') && ft_iswhitespace(line[i + 1]))
		return (parse_color_line(data, line));
	if (ft_strncmp(line + i, "NO", 2) == 0 && ft_iswhitespace(line[i + 2]))
		return (parse_texture_line(data, line, NORTH));
	if (ft_strncmp(line + i, "SO", 2) == 0 && ft_iswhitespace(line[i + 2]))
		return (parse_texture_line(data, line, SOUTH));
	if (ft_strncmp(line + i, "EA", 2) == 0 && ft_iswhitespace(line[i + 2]))
		return (parse_texture_line(data, line, EAST));
	if (ft_strncmp(line + i, "WE", 2) == 0 && ft_iswhitespace(line[i + 2]))
		return (parse_texture_line(data, line, WEST));
	if (is_map_token(line[i]))
	{
		data->parsing.is_map = 1;
		return (parse_map_line(data, line));
	}
	return (0);
}

int	read_file(t_data *data, int fd)
{
	char	*line;

	line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (parse_line(data, line) == ERROR)
			return (free(line), ERROR);
		free(line);
	}
	if (data->parsing.is_map == 0)
		return (line_error("EOF", NO_MAP));
	data->map = ft_lsttotab(data->parsing.lst_map, data->map_x);
	ft_lstclear(&data->parsing.lst_map, &free);
	if (parse_map(data) == ERROR)
		return (ERROR);
	if (data->has_ceiling == 0 || data->has_floor == 0)
		return (line_error("EOF", MISSING_COLOR));
	return (0);
}

int	parse_file(t_data *data, char *file)
{
	int	size;
	int	fd;

	data->parsing.is_map = 0;
	size = ft_strlen(file);
	if (size < 5 || ft_strcmp(file + size - 4, ".cub") != 0)
	{
		printf("File has no name, or is missing extension .cub\n");
		return (1);
	}
	fd = open(file, O_RDONLY);
	return (read_file(data, fd));
}
