/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:13:22 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/14 18:07:55 by maagosti         ###   ########.fr       */
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
	// data->img2 = mlx_new_image(data->mlx, 500, 500);
	// data->draw2 = (t_color *)mlx_get_data_addr(data->img2, &t, &t, &t);
	mlx_hook(data->win, 33, 1L << 17, mlx_loop_end, data->mlx);
	mlx_hook(data->win, 2, 1L << 0, hook_keydown, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	free_data(t_data *data)
{
	free(data->texture.north);
	free(data->texture.south);
	free(data->texture.east);
	free(data->texture.west);
	ft_free_tab(data->map);
	free(data);
}

void	init_data(t_data *data)
{
	data->parsing.lst_map = NULL;
}

int	main(int ac, char **av)
{
	t_data		*data;

	if (ac != 2)
	{
		printf("Invalid arguments:\n./cub3d <map.cub>\n");
		return (1);
	}
	data = ft_calloc(sizeof(t_data), 1);
	init_data(data);
	if (parse_file(data, av[1]) == ERROR)
		return (free_data(data), ERROR);

	printf("Parsing result:\n");
	printf("Floor: %d,%d,%d\n", data->floor.r, data->floor.g, data->floor.b);
	printf("Ceiling: %d,%d,%d\n\n", data->ceiling.r, data->ceiling.g, data->ceiling.b);

	printf("Player:\n");
	printf(" -> x: %f\n", data->player.pos_x);
	printf(" -> y: %f\n", data->player.pos_y);
	printf(" -> rotation: %f\n\n", data->player.rotation);

	printf("North: %s\n", (char *)(data->texture.north));
	printf("South: %s\n", (char *)data->texture.south);
	printf("East: %s\n", (char *)data->texture.east);
	printf("West: %s\n\nMap:\n", (char *)data->texture.west);

	ft_print_tab(data->map);

	start_mlx(data);
	// mlx_loop(data->mlx);
	mlx_destroy_image(data->mlx, data->img);

	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free_data(data);
}
