/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 01:44:35 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/25 02:04:33 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_to_rad(double angle)
{
	return (angle * PI / 180);
}

double	rad_to_deg(double angle)
{
	return (angle * 180 / PI);
}

t_ray	*new_ray(double x, double y, double angle)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	ray->x = x;
	ray->y = y;
	ray->dirx = cos(deg_to_rad(angle));
	ray->diry = sin(deg_to_rad(angle));
	ray->wall_type = NONE;
	ray->deltax = fabs(1 / ray->dirx);
	ray->deltay = fabs(1 / ray->diry);
	ray->stepx = (ray->dirx >= 0) + (ray->dirx < 0) * -1;
	ray->stepy = (ray->diry >= 0) + (ray->diry < 0) * -1;
	if (ray->dirx >= 0)
		ray->distx = (floor(x) + 1 - x) * ray->deltax;
	else
		ray->distx = (x - floor(x)) * ray->deltax;
	if (ray->diry >= 0)
		ray->disty = (floor(y) + 1 - y) * ray->deltay;
	else
		ray->disty = (y - floor(y)) * ray->deltay;
	return (ray);
}

t_ray	*raycast(double x, double y, double angle, t_data *data)
{
	t_ray	*ray;

	ray = new_ray(x, y, angle);
	while (data->map[(int)ray->y][(int)ray->x] == EMPTY)
	{
		if (ray->distx < ray->disty)
		{
			ray->distx += ray->deltax;
			ray->x += ray->stepx;
			ray->impactx = floor(ray->x) + (1 - ray->stepx) / 2;
			ray->impacty = y + (ray->impactx - x) * ray->diry / ray->dirx;
			ray->side = 0;
		}
		else
		{
			ray->disty += ray->deltay;
			ray->y += ray->stepy;
			ray->impacty = floor(ray->y) + (1 - ray->stepy) / 2;
			ray->impactx = x + (ray->impacty - y) * ray->dirx / ray->diry;
			ray->side = 1;
		}
	}
	ray->dist = sqrt(pow(ray->impactx - x, 2) + pow(ray->impacty - y, 2));
	return (ray);
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

void	draw_point(t_data *data, int x, int y, t_color color)
{
	if (y < 0 || x < 0 || y >= WIN_Y
		|| x >= WIN_X)
		return ;
	data->draw[WIN_X * y + x] = color;
}

t_color	get_texture_color(int y, int height, double angle, t_data *data)
{
	t_texture	*texture;
	int			index;
	double		x_ratio;

	if (data->ray->side == 1)
	{
		x_ratio = data->ray->impactx - floor(data->ray->impactx);
		if (angle > 180)
			texture = &data->texture[NORTH];
		else
		{
			x_ratio = 1 - x_ratio;
			texture = &data->texture[SOUTH];
		}
	}
	else
	{
		x_ratio = data->ray->impacty - floor(data->ray->impacty);
		if (angle < 270 && angle > 90)
		{
			texture = &data->texture[EAST];
			x_ratio = 1 - x_ratio;
		}
		else
			texture = &data->texture[WEST];
	}
	index = ((int)((double)y / height * texture->sizey) * texture->sizex);
	index += texture->sizex * fabs(x_ratio);
	return (texture->draw[index]);
}

void	display_ray(int x, double angle, t_data *data)
{
	int	y;
	int	height;

	height = WIN_Y / data->ray->dist;
	y = -1;
	while (++y < WIN_Y)
	{
		if (y < -height / 2 + WIN_Y / 2)
			draw_point(data, x, y, data->ceiling);
		else if (y > height / 2 + WIN_Y / 2)
			draw_point(data, x, y, data->floor);
		else
			draw_point(data, x, y,
				get_texture_color(y - (-height / 2 + WIN_Y / 2),
				height + 1, angle, data));
	}
}

double	fix_angle(double angle)
{
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	return (angle);
}

void	calculate_img(t_data *data)
{
	double	x;
	double	ray_angle;

	x = 0;
	while (++x < WIN_X)
	{
		free(data->ray);
		ray_angle = data->player.rotation - (FOV / 2) + (FOV * x / (WIN_X - 1));
		ray_angle = fix_angle(ray_angle);
		data->ray = raycast(data->player.pos_x, data->player.pos_y,
				ray_angle, data);
		display_ray(x, ray_angle, data);
	}
}
