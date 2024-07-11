/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:48:57 by dferjul           #+#    #+#             */
/*   Updated: 2024/07/11 23:03:15 by maagosti         ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}
