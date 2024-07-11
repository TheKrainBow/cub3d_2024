/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:27:34 by dferjul           #+#    #+#             */
/*   Updated: 2024/07/12 01:19:26 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_move_up(t_data *data)
{
	double	move_step;
	double	new_x;
	double	new_y;

	move_step = 0.2;
	new_x = data->player.pos_x + \
		cos(data->player.rotation * PI / 180) * move_step;
	new_y = data->player.pos_y + \
		sin(data->player.rotation * PI / 180) * move_step;
	if (data->map[(int)new_y][(int)new_x] != WALL)
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
}

void	ft_move_down(t_data *data)
{
	double	move_step;
	double	new_x;
	double	new_y;

	move_step = 0.2;
	new_x = data->player.pos_x - \
		cos(data->player.rotation * PI / 180) * move_step;
	new_y = data->player.pos_y - \
		sin(data->player.rotation * PI / 180) * move_step;
	if (data->map[(int)new_y][(int)new_x] != WALL)
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
}

void	ft_move_left(t_data *data)
{
	double	move_step;
	double	new_x;
	double	new_y;

	move_step = 0.2;
	new_x = data->player.pos_x + \
		sin(data->player.rotation * PI / 180) * move_step;
	new_y = data->player.pos_y - \
		cos(data->player.rotation * PI / 180) * move_step;
	if (data->map[(int)new_y][(int)new_x] != WALL)
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
}

void	ft_move_right(t_data *data)
{
	double	new_x;
	double	new_y;
	double	move_step;

	move_step = 0.2;
	new_x = data->player.pos_x - \
		sin(data->player.rotation * PI / 180) * move_step;
	new_y = data->player.pos_y + \
		cos(data->player.rotation * PI / 180) * move_step;
	if (data->map[(int)new_y][(int)new_x] != WALL)
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
}
