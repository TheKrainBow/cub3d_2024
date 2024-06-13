/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:13:22 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/13 19:29:01 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hook_keydown(int key_code, void *param)
{
	t_data	*data;

	data = param;
	if (key_code == KEY_ESC)
	{
		ft_putstr("ESC pressed\nExiting\n");
		mlx_loop_end(data->mlx);
	}
	return (1);
}

void	start_mlx(t_data *data)
{
	int		t;

	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 500, 500, "Cub3D");
	data->img = mlx_new_image(data->mlx, 500, 500);
	data->draw = (t_color *)mlx_get_data_addr(data->img, &t, &t, &t);
	data->img2 = mlx_new_image(data->mlx, 500, 500);
	data->draw2 = (t_color *)mlx_get_data_addr(data->img2, &t, &t, &t);
	mlx_hook(data->win, 33, 1L << 17, mlx_loop_end, data->mlx);
	mlx_hook(data->win, 2, 1L << 0, hook_keydown, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	free_data(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_image(data->mlx, data->img2);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data);
}

int main()
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	start_mlx(data);
	mlx_loop(data->mlx);
	free_data(data);
}