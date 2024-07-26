/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 02:47:34 by dferjul           #+#    #+#             */
/*   Updated: 2024/07/26 02:47:34 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	toggle_mouse(t_data *data)
{
	if (data->inputs.allow_mouse == 1)
	{
		data->inputs.allow_mouse = 0;
		mlx_mouse_show(data->mlx, data->win);
	}
	else
	{
		data->inputs.allow_mouse = 1;
		mlx_mouse_hide(data->mlx, data->win);
	}
}

int	mouse_hook(int x, int y, t_data *data)
{
	if (!data->inputs.allow_mouse)
		return (0);
	data->player.offset += (WIN_Y / 2 - y) / ((double)WIN_Y / WIN_X) / 20;
	data->player.rotation -= (WIN_X / 2 - x) / ((double)WIN_X / WIN_Y) / 50;
	data->player.rotation = (data->player.rotation);
	return (0);
}
