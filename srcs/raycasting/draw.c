/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:09:54 by maagosti          #+#    #+#             */
/*   Updated: 2024/07/26 02:53:02 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	point(int x, int y)
{
	t_point	dest;

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
