/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 01:44:35 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/24 04:41:23 by maagosti         ###   ########.fr       */
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
		}
		else
		{
			ray->disty += ray->deltay;
			ray->y += ray->stepy;
			ray->impacty = floor(ray->y) + (1 - ray->stepy) / 2;
			ray->impactx = x + (ray->impacty - y) * ray->dirx / ray->diry;
		}
	}
	ray->dist = sqrt(pow(ray->impactx - x, 2) + pow(ray->impacty - y, 2));
	return (ray);
}

t_color	color(int r, int g, int b)
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

void	display_ray(int x, double angle, t_data *data)
{
	double	y;
	double height;

	(void)angle;
	height = WIN_Y / data->ray->dist;
	y = -1;
	while (++y < WIN_Y)
	{
		if (y < -height / 2 + WIN_Y / 2)
			draw_point(data, x, y, data->ceiling);
		else if (y > height / 2 + WIN_Y / 2)
			draw_point(data, x, y, data->floor);
		else
			draw_point(data, x, y, color(124, 56, 98));
	}
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
	
		data->ray = raycast(data->player.pos_x, data->player.pos_y, ray_angle, data);
		display_ray(x, ray_angle, data);
	}
}