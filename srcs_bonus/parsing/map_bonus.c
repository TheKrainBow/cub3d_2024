/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:15:48 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/01 17:16:07 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				if ((j == 0 || i == 0 || j == data->map_y - 1
						|| i == data->map_x - 1))
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
