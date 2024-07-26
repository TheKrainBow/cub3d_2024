/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:48:57 by dferjul           #+#    #+#             */
/*   Updated: 2024/07/26 15:06:46 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	toggle_map(t_data *data)
{
	int	t;

	if (!data->inputs.has_map)
	{
		data->win_map = mlx_new_window(data->mlx, data->map_x * MAP_SCALE,
				data->map_y * MAP_SCALE, "Minimap");
		data->img_map = mlx_new_image(data->mlx, data->map_x * MAP_SCALE,
				data->map_y * MAP_SCALE);
		data->draw_map = (t_color *)mlx_get_data_addr(data->img_map,
				&t, &t, &t);
		mlx_hook(data->win_map, 33, 1L << 17, toggle_map, data);
		mlx_hook(data->win_map, 2, 1L << 0, key_press, data);
		mlx_hook(data->win_map, 3, 1L << 1, key_up, data);
		mlx_hook(data->win_map, 6, 1L << 6, mouse_hook, data);
		draw_map_point(data, 10, 10, color(255, 0, 0));
		mlx_put_image_to_window(data->mlx, data->win_map, data->img_map, 0, 0);
		data->inputs.has_map = 1;
	}
	else
	{
		mlx_destroy_window(data->mlx, data->win_map);
		mlx_destroy_image(data->mlx, data->img_map);
		data->inputs.has_map = 0;
	}
	return (1);
}

void	escape_key(t_data *data)
{
	ft_putstr("ESC pressed\nExiting\n");
	mlx_loop_end(data->mlx);
}

int	key_press(int key_code, t_data *data)
{
	if (key_code == KEY_ESC)
		escape_key(data);
	if (key_code == W_KEY || key_code == Z_KEY)
		data->inputs.forward = 1;
	if (key_code == S_KEY)
		data->inputs.backward = 1;
	if (key_code == A_KEY || key_code == Q_KEY)
		data->inputs.left = 1;
	if (key_code == D_KEY)
		data->inputs.right = 1;
	if (key_code == 65361)
		data->inputs.rot_left = 1;
	if (key_code == 65363)
		data->inputs.rot_right = 1;
	if (key_code == 65362)
		data->inputs.rot_up = 1;
	if (key_code == 65364)
		data->inputs.rot_down = 1;
	if (key_code == 108)
		toggle_mouse(data);
	if (key_code == 109)
		toggle_map(data);
	return (EXIT_SUCCESS);
}

int	key_up(int key_code, t_data *data)
{
	if (key_code == W_KEY || key_code == Z_KEY)
		data->inputs.forward = 0;
	if (key_code == S_KEY)
		data->inputs.backward = 0;
	if (key_code == A_KEY || key_code == Q_KEY)
		data->inputs.left = 0;
	if (key_code == D_KEY)
		data->inputs.right = 0;
	if (key_code == 65361)
		data->inputs.rot_left = 0;
	if (key_code == 65363)
		data->inputs.rot_right = 0;
	if (key_code == 65362)
		data->inputs.rot_up = 0;
	if (key_code == 65364)
		data->inputs.rot_down = 0;
	return (EXIT_SUCCESS);
}
