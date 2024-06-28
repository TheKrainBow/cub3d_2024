/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:48:57 by dferjul           #+#    #+#             */
/*   Updated: 2024/06/28 02:17:35 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int key_code, t_data *data)
{
	if (key_code == KEY_ESC)
	{
		ft_putstr("ESC pressed\nExiting\n");
		mlx_loop_end(data->mlx);
	}
	if (key_code == W_KEY || key_code == 119)
		ft_move_up(data);
	if (key_code == S_KEY || key_code == 115)
		ft_move_down(data);
	if (key_code == A_KEY || key_code == 97)
		ft_move_left(data);
	if (key_code == D_KEY || key_code == 100)
		ft_move_right(data);
	print_map(data);
	return (EXIT_SUCCESS);
}
