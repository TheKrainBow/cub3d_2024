/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:09:54 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/30 18:41:47 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color	color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color	dest;

	dest.r = r;
	dest.g = g;
	dest.b = b;
	dest.a = 1;
	return (dest);
}

t_color	get_texture_color(int y, int height, double angle, t_data *data)
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
	int	y;
	int	height;
	double	correctedDist;

	correctedDist = data->ray->dist * cos(deg_to_rad(fix_angle(angle)) - deg_to_rad(fix_angle(data->player.rotation)));
	height = WIN_Y / correctedDist;
	y = -1;
	while (++y < WIN_Y)
	{
		if (y <= -height / 2 + WIN_Y / 2)
			draw_point(data, x, y, data->ceiling);
		else if (y >= height / 2 + WIN_Y / 2)
			draw_point(data, x, y, data->floor);
		else
			draw_point(data, x, y,
				get_texture_color(y - (-height / 2 + WIN_Y / 2),
					height + 1, angle, data));
	}
}

void	draw_point(t_data *data, int x, int y, t_color color)
{
	if (y < 0 || x < 0 || y >= WIN_Y
		|| x >= WIN_X)
		return ;
	data->draw[WIN_X * y + x] = color;
}
