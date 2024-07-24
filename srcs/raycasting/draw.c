/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:09:54 by maagosti          #+#    #+#             */
/*   Updated: 2024/07/24 18:31:50 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	point(int x, int y)
{
	t_point dest;

	dest.x = x;
	dest.y = y;
	return (dest);
}

t_color	color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color	dest;

	dest.r = r;
	dest.g = g;
	dest.b = b;
	dest.a = 1;
	return (dest);
}

t_color	get_texture_color(int y, double height, double angle, t_data *data)
{
	t_texture	*texture;
	int			index;
	double		x_ratio;

	if (data->ray->side == 1)
	{
		x_ratio = data->ray->impactx - floor(data->ray->impactx);
		texture = &data->texture[(angle <= 180)];
		if (angle <= 180)
			x_ratio = 1 - x_ratio;
	}
	else
	{
		x_ratio = data->ray->impacty - floor(data->ray->impacty);
		texture = &data->texture[2 + !(angle < 270 && angle > 90)];
		if (angle < 270 && angle > 90)
			x_ratio = 1 - x_ratio;
	}
	index = (floor((double)y / height * texture->sizey) * texture->sizex);
	index += texture->sizex * fabs(x_ratio);
	return (texture->draw[index]);
}

void	display_ray(int x, double angle, t_data *data)
{
	int		y;
	int		height;
	double	dist;

	dist = data->ray->dist * cos(deg_to_rad(fix_angle(angle))
			- deg_to_rad(fix_angle(data->player.rotation)));
	height = WIN_Y / dist;
	y = -1;
	while (++y < WIN_Y)
	{
		if (y <= -height / 2 + WIN_Y / 2 + data->player.offset)
			draw_point(data, x, y, data->ceiling);
		else if (y >= height / 2 + WIN_Y / 2 + data->player.offset)
			draw_point(data, x, y, data->floor);
		else
			draw_point(data, x, y,
				get_texture_color(y - (-height / 2 + WIN_Y / 2 + data->player.offset),
					height, angle, data));
	}
}

void	draw_point(t_data *data, int x, int y, t_color color)
{
	if (y < 0 || x < 0 || y >= WIN_Y
		|| x >= WIN_X)
		return ;
	data->draw[WIN_X * y + x] = color;
}

void	draw_map_point(t_data *data, int x, int y, t_color color)
{
	if (y < 0 || x < 0 || y >= (data->map_y * MAP_SCALE)
		|| x >= (data->map_x * MAP_SCALE))
		return ;
	data->draw_map[(data->map_x * MAP_SCALE) * y + x] = color;
}

void	draw_map(t_data *data)
{
	int		x;
	int		y;
	t_color px;

	y = -1;
	while (++y < data->map_y * MAP_SCALE)
	{
		x = -1;
		while (++x < data->map_x * MAP_SCALE)
		{
			if (data->map[y / MAP_SCALE][x / MAP_SCALE] == WALL)
				px = color(255, 0, 0);
			else
				px = color(255, 255, 255);
			draw_map_point(data, x, y, px);
		}
	}
	draw_map_point(data, data->player.pos_x * MAP_SCALE, data->player.pos_y * MAP_SCALE, color(0, 0, 0));
	draw_map_point(data, data->player.pos_x * MAP_SCALE - 1, data->player.pos_y * MAP_SCALE, color(0, 0, 0));
	draw_map_point(data, data->player.pos_x * MAP_SCALE + 1, data->player.pos_y * MAP_SCALE, color(0, 0, 0));
	draw_map_point(data, data->player.pos_x * MAP_SCALE, data->player.pos_y * MAP_SCALE - 1, color(0, 0, 0));
	draw_map_point(data, data->player.pos_x * MAP_SCALE, data->player.pos_y * MAP_SCALE + 1, color(0, 0, 0));
	mlx_put_image_to_window(data->mlx, data->win_map, data->img_map, 0, 0);
}
