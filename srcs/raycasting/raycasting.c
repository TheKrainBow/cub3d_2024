/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 01:44:35 by maagosti          #+#    #+#             */
/*   Updated: 2024/07/24 17:47:55 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_to_rad(double angle)
{
	return (angle * PI / 180);
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

	if (x < 0 || x >= data->map_x || y < 0 || y >= data->map_y)
		return (NULL);
	ray = new_ray(x, y, angle);
	while (data->map[(int)ray->y][(int)ray->x] == EMPTY)
	{
		ray->side = !(ray->distx < ray->disty);
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

double	fix_angle(double angle)
{
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	return (angle);
}


int		ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	draw_line(t_data *data, t_point a, t_point b, t_color color)
{
	int			i;
	t_point		d;
	double		steps;

	d.x = b.x - a.x;
	d.y = b.y - a.y;
	steps = ft_max(ft_abs(d.x), ft_abs(d.y));
	d.x /= steps;
	d.y /= steps;
	i = -1;
	while (++i <= steps)
	{
		draw_point(data, a.x, a.y, color);
		a.x = a.x + d.x;
		a.y = a.y + d.y;
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
		ray_angle = fix_angle(ray_angle);
		data->ray = raycast(data->player.pos_x, data->player.pos_y,
				ray_angle, data);
		display_ray(x, ray_angle, data);
	}
	draw_line(data, point(WIN_X / 2, WIN_Y / 2 - 5), point(WIN_X / 2, WIN_Y / 2 - 10), color(0, 255, 0));
	draw_line(data, point(WIN_X / 2, WIN_Y / 2 + 5), point(WIN_X / 2, WIN_Y / 2 + 10), color(0, 255, 0));
	draw_line(data, point(WIN_X / 2 - 5, WIN_Y / 2), point(WIN_X / 2 - 10, WIN_Y / 2), color(0, 255, 0));
	draw_line(data, point(WIN_X / 2 + 5, WIN_Y / 2), point(WIN_X / 2 + 10, WIN_Y / 2), color(0, 255, 0));
	draw_point(data, WIN_X / 2, WIN_Y / 2, color(255, 0, 0));
}
