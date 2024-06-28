/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:13:22 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/27 21:24:57 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* int	hook_keydown(int key_code, void *param)
{
	t_data	*data;

	data = param;
	if (key_code == KEY_ESC)
	{
		ft_putstr("ESC pressed\nExiting\n");
		mlx_loop_end(data->mlx);
	}
	return (1);
} */

int	hook_loop(t_data *data)
{
	(void)data;
	//data->player.rotation += 2;
	calculate_img(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (1);
}

int	free_data(t_data *data)
{
	ft_free_tab(data->map);
	free(data->ray);
	free(data);
	return (ERROR);
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
	texture->draw = (t_color *)mlx_get_data_addr(texture->ptr, &trash, &trash, &trash);
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

void	init_data(t_data *data)
{
	data->parsing.lst_map = NULL;
	data->ray = NULL;
}

void	print_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map && data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->ray
				&& j == (int)data->ray->x && i == (int)data->ray->y)
				ft_putstr(RED "██" WHITE);
			else if (data->map[i][j] == WALL)
				ft_putstr("██");
			if (i == (int)data->player.pos_y && j == (int)data->player.pos_x)
				ft_putstr(GREEN "██" WHITE);
			else if (data->map[i][j] == EMPTY)
				ft_putstr("  ");
		}
		ft_putchar('\n');
	}
}

void	print_data(t_data *data)
{
	printf("Parsing result:\n");
	printf("Floor: %d,%d,%d\n", data->floor.r, data->floor.g, data->floor.b);
	printf("Ceiling: %d,%d,%d\n\n", data->ceiling.r, data->ceiling.g,
		data->ceiling.b);
	printf("Player:\n");
	printf(" -> x: %f\n", data->player.pos_x);
	printf(" -> y: %f\n", data->player.pos_y);
	printf(" -> rotation: %f\n\n", data->player.rotation);
	printf("\n\nMap:\n");
	print_map(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
	{
		printf("Invalid arguments:\n./cub3d <map.cub>\n");
		return (1);
	}
	data = ft_calloc(sizeof(t_data), 1);
	init_data(data);
	if (parse_file(data, av[1]) == ERROR)
		return (free_data(data));
	if (start_mlx(data) == ERROR)
		return (free_data(data));
	calculate_img(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	print_data(data);
	mlx_loop(data->mlx);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_image(data->mlx, data->img2);
	mlx_destroy_image(data->mlx, data->texture[NORTH].ptr);
	mlx_destroy_image(data->mlx, data->texture[SOUTH].ptr);
	mlx_destroy_image(data->mlx, data->texture[WEST].ptr);
	mlx_destroy_image(data->mlx, data->texture[EAST].ptr);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free_data(data);
}
