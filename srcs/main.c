/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:13:22 by maagosti          #+#    #+#             */
/*   Updated: 2024/07/24 16:26:05 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_data(t_data *data)
{
	ft_free_tab(data->map);
	free(data->texture[NORTH].path);
	free(data->texture[SOUTH].path);
	free(data->texture[EAST].path);
	free(data->texture[WEST].path);
	free(data->ray);
	free(data);
	return (ERROR);
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
			if (data->map[i][j] == WALL)
				ft_putstr("██");
			if (i == (int)data->player.pos_y && j == (int)data->player.pos_x)
				ft_putstr(GREEN "██" WHITE);
			else if (data->map[i][j] == EMPTY)
				ft_putstr("  ");
		}
		ft_putchar('\n');
	}
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
	if (parse_file(data, av[1]) == ERROR)
		return (free_data(data));
	if (start_mlx(data) == ERROR)
	{
		mlx_destroy(data);
		free_data(data);
		return (0);
	}
	calculate_img(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop(data->mlx);
	mlx_destroy(data);
	free_data(data);
	exit(0);
}
