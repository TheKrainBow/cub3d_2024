/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:03:06 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/01 19:03:44 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hook_loop(t_data *data)
{
	if (data->inputs.forward)
		ft_move_up(data);
	if (data->inputs.backward)
		ft_move_down(data);
	if (data->inputs.left)
		ft_move_left(data);
	if (data->inputs.right)
		ft_move_right(data);
	if (data->inputs.rot_right)
		ft_turn_right(data);
	if (data->inputs.rot_left)
		ft_turn_left(data);
	if (data->inputs.rot_up)
		ft_turn_up(data);
	if (data->inputs.rot_down)
		ft_turn_down(data);
	calculate_img(data);
	if (data->inputs.allow_mouse)
		mlx_mouse_move(data->mlx, data->win, WIN_X / 2, WIN_Y / 2);
	if (data->inputs.has_map)
		draw_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (1);
}

int	open_texture(void *mlx, t_texture *texture, t_wall text)
{
	int		trash;
	char	*tmp;

	if (!texture->path)
	{
		ft_putstr_fd("There are no ", 2);
		ft_putendl_fd(texture_to_str(text), 2);
		return (ERROR);
	}
	tmp = ft_strtrim(texture->path, " \f\t\n\r\v");
	texture->ptr = mlx_xpm_file_to_image(mlx, tmp,
			&texture->sizex, &texture->sizey);
	free(tmp);
	if (!texture->ptr)
	{
		ft_putstr_fd("Error while opening texture '", 2);
		ft_putendl_fd(texture->path, 2);
		return (ERROR);
	}
	texture->draw = (t_color *)mlx_get_data_addr(texture->ptr,
			&trash, &trash, &trash);
	return (VALID);
}

int	open_textures(t_data *data)
{
	if (open_texture(data->mlx, &data->texture[NORTH], NORTH) == ERROR)
		return (ERROR);
	if (open_texture(data->mlx, &data->texture[SOUTH], SOUTH) == ERROR)
		return (ERROR);
	if (open_texture(data->mlx, &data->texture[EAST], EAST) == ERROR)
		return (ERROR);
	if (open_texture(data->mlx, &data->texture[WEST], WEST) == ERROR)
		return (ERROR);
	return (VALID);
}

int	start_mlx(t_data *data)
{
	int	t;

	data->mlx = mlx_init();
	if (open_textures(data) == ERROR)
		return (ERROR);
	data->win = mlx_new_window(data->mlx, WIN_X, WIN_Y, "Cub3D");
	data->img = mlx_new_image(data->mlx, WIN_X, WIN_Y);
	data->draw = (t_color *)mlx_get_data_addr(data->img, &t, &t, &t);
	data->img2 = mlx_new_image(data->mlx, WIN_X, WIN_Y);
	data->draw2 = (t_color *)mlx_get_data_addr(data->img2, &t, &t, &t);
	mlx_hook(data->win, 33, 1L << 17, mlx_loop_end, data->mlx);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_up, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_hook, data);
	mlx_loop_hook(data->mlx, hook_loop, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	data->map_scale = MAP_SCALE;
	while (data->map_x * data->map_scale > 500
		|| data->map_y * data->map_scale + 100 > 500)
		data->map_scale--;
	return (VALID);
}

void	mlx_destroy(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->img2)
		mlx_destroy_image(data->mlx, data->img2);
	if (data->texture[NORTH].ptr)
		mlx_destroy_image(data->mlx, data->texture[NORTH].ptr);
	if (data->texture[SOUTH].ptr)
		mlx_destroy_image(data->mlx, data->texture[SOUTH].ptr);
	if (data->texture[WEST].ptr)
		mlx_destroy_image(data->mlx, data->texture[WEST].ptr);
	if (data->texture[EAST].ptr)
		mlx_destroy_image(data->mlx, data->texture[EAST].ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->inputs.has_map)
	{
		mlx_destroy_window(data->mlx, data->win_map);
		mlx_destroy_image(data->mlx, data->img_map);
	}
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}
