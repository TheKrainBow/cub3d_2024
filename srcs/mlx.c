/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:03:06 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/30 18:07:42 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hook_loop(t_data *data)
{
	calculate_img(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (1);
}

int	open_texture(void *mlx, t_texture *texture)
{
	int		trash;
	void	*tmp;

	tmp = texture->ptr;
	texture->ptr = mlx_xpm_file_to_image(mlx, tmp,
			&texture->sizex, &texture->sizey);
	if (!texture->ptr)
	{
		ft_putstr_fd("Error while openning texture ", 2);
		ft_putstr_fd(tmp, 2);
		free(tmp);
		return (ERROR);
	}
	texture->draw = (t_color *)mlx_get_data_addr(texture->ptr,
			&trash, &trash, &trash);
	free(tmp);
	return (VALID);
}

int	open_textures(t_data *data)
{
	if (open_texture(data->mlx, &data->texture[NORTH]) == ERROR)
		return (ERROR);
	if (open_texture(data->mlx, &data->texture[SOUTH]) == ERROR)
		return (ERROR);
	if (open_texture(data->mlx, &data->texture[EAST]) == ERROR)
		return (ERROR);
	if (open_texture(data->mlx, &data->texture[WEST]) == ERROR)
		return (ERROR);
	return (VALID);
}

int	start_mlx(t_data *data)
{
	int	t;

	data->mlx = mlx_init();
	if (open_textures(data) == ERROR)
	{
		mlx_destroy_display(data->mlx);
		return (ERROR);
	}
	data->win = mlx_new_window(data->mlx, WIN_X, WIN_Y, "Cub3D");
	data->img = mlx_new_image(data->mlx, WIN_X, WIN_Y);
	data->draw = (t_color *)mlx_get_data_addr(data->img, &t, &t, &t);
	data->img2 = mlx_new_image(data->mlx, WIN_X, WIN_Y);
	data->draw2 = (t_color *)mlx_get_data_addr(data->img2, &t, &t, &t);
	mlx_hook(data->win, 33, 1L << 17, mlx_loop_end, data->mlx);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_loop_hook(data->mlx, hook_loop, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (VALID);
}

void	mlx_destroy(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_image(data->mlx, data->img2);
	mlx_destroy_image(data->mlx, data->texture[NORTH].ptr);
	mlx_destroy_image(data->mlx, data->texture[SOUTH].ptr);
	mlx_destroy_image(data->mlx, data->texture[WEST].ptr);
	mlx_destroy_image(data->mlx, data->texture[EAST].ptr);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
}
