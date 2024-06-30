/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:48:57 by dferjul           #+#    #+#             */
/*   Updated: 2024/06/30 17:05:06 by maagosti         ###   ########.fr       */
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
	if (key_code == W_KEY || key_code == Z_KEY)
		ft_move_up(data);
	if (key_code == S_KEY)
		ft_move_down(data);
	if (key_code == A_KEY || key_code == Q_KEY)
		ft_move_left(data);
	if (key_code == D_KEY)
		ft_move_right(data);
	if (key_code == 65361)
		ft_turn_left(data);
	if (key_code == 65363)
		ft_turn_right(data);
	return (EXIT_SUCCESS);
}
