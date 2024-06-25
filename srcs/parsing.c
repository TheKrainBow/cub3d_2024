/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:49:26 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/25 01:28:09 by maagosti         ###   ########.fr       */
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

int	is_map_token(char c)
{
	return (c == EMPTY || c == WALL || c == PLAYER_NORTH || c == PLAYER_SOUTH
		|| c == PLAYER_EAST || c == PLAYER_WEST);
}

int	parse_map_line(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(line[i]) || is_map_token(line[i]))
		i++;
	if (line[i])
		return (ft_lstclear(&data->parsing.lst_map, &free), line_error(line,
				UNEXPECTED_TOKEN));
	ft_lstadd_back(&data->parsing.lst_map, ft_lstnew(ft_strdup(line)));
	if (i > data->map_x)
		data->map_x = i;
	data->map_y++;
	return (0);
}

int	parse_color(char *line, int *i, unsigned char *color)
{
	while (ft_iswhitespace(line[*i]))
		(*i)++;
	if (!ft_isdigit(line[*i]))
		return (line_error(line, NOT_INT));
	*color = ft_atoi(line + *i);
	if (*color > 255)
		return (line_error(line, NOT_INT));
	while (ft_isdigit(line[*i]) || ft_iswhitespace(line[*i]))
		(*i)++;
	return (0);
}

int	parse_color_line(t_data *data, char *line)
{
	t_color	*color;
	int		i;

	i = 0;
	if (line[i] == 'F')
		color = &data->floor;
	else
		color = &data->ceiling;
	i++;
	if (parse_color(line, &i, &color->r) == ERROR)
		return (ERROR);
	if (line[i] != ',')
		return (line_error(line, MISSING_TOKEN));
	i++;
	if (parse_color(line, &i, &color->g) == ERROR)
		return (ERROR);
	if (line[i] != ',')
		return (line_error(line, MISSING_TOKEN));
	i++;
	if (parse_color(line, &i, &color->b) == ERROR)
		return (ERROR);
	if (line[i] != '\0')
		return (line_error(line, UNEXPECTED_TOKEN));
	return (0);
}

int	parse_texture_line(t_data *data, char *line, t_wall type)
{
	int		i;
	void	**texture;

	texture = &data->texture[type].ptr;
	i = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	i += 2;
	while (ft_iswhitespace(line[i]))
		i++;
	*texture = ft_strdup(line + i);
	while (line[i] && !ft_iswhitespace(line[i]))
		i++;
	while (ft_iswhitespace(line[i]))
		i++;
	if (line[i])
		return (line_error(line, UNEXPECTED_TOKEN));
	return (0);
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

int	is_player(int c)
{
	return (c == PLAYER_NORTH || c == PLAYER_SOUTH || c == PLAYER_EAST
		|| c == PLAYER_WEST);
}

double	parse_rotation(int c)
{
	if (c == PLAYER_EAST)
		return (0);
	if (c == PLAYER_NORTH)
		return (270);
	if (c == PLAYER_WEST)
		return (180);
	return (90);
}

int	is_map_border(char c)
{
	return (ft_iswhitespace(c));
}

int	find_player(t_data *data)
{
	int	i;
	int	j;

	j = -1;
	while (data->map[++j])
	{
		i = -1;
		while (data->map[j][++i])
		{
			if (is_player(data->map[j][i]))
			{
				if (data->parsing.has_player == 1)
					return (line_error(data->map[j], MULTIPLE_PLAYER));
				data->parsing.has_player = 1;
				data->player.pos_x = i + 0.5;
				data->player.pos_y = j + 0.5;
				data->player.rotation = parse_rotation(data->map[j][i]);
				data->map[j][i] = EMPTY;
			}
		}
	}
	return (VALID);
}

int	check_closed_map(t_data *data)
{
	int	i;
	int	j;

	j = -1;
	while (data->map[++j])
	{
		i = -1;
		while (data->map[j][++i])
		{
			if (data->map[j][i] == EMPTY)
			{
				if ((j == 0 || i == 0 || j == data->map_y || i == data->map_x))
					return (line_error(data->map[j], "Map not closed"));
				if (ft_iswhitespace(data->map[j - 1][i])
					|| ft_iswhitespace(data->map[j + 1][i])
					|| ft_iswhitespace(data->map[j][i - 1])
					|| ft_iswhitespace(data->map[j][i + 1]))
					return (line_error(data->map[j], "Map not closed"));
			}
		}
	}
	return (VALID);
}

int	parse_map(t_data *data)
{
	int	i;
	int	j;

	if (find_player(data) == ERROR)
		return (ERROR);
	if (check_closed_map(data) == ERROR)
		return (ERROR);
	j = -1;
	while (data->map[++j])
	{
		i = -1;
		while (data->map[j][++i])
		{
			if (ft_iswhitespace(data->map[j][i]))
				data->map[j][i] = EMPTY;
		}
	}
	return (VALID);
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
