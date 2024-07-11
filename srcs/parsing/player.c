/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:22:17 by maagosti          #+#    #+#             */
/*   Updated: 2024/07/12 01:19:26 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
