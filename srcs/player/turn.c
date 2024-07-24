/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:13:52 by maagosti          #+#    #+#             */
/*   Updated: 2024/07/24 17:32:13 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_turn_right(t_data *data)
{
	data->player.rotation += 5;
	data->player.rotation = fix_angle(data->player.rotation);
}

void	ft_turn_left(t_data *data)
{
	data->player.rotation -= 5;
	data->player.rotation = fix_angle(data->player.rotation);
}

void	ft_turn_up(t_data *data)
{
	if (data->player.offset < +3000)
		data->player.offset += 30;
}

void	ft_turn_down(t_data *data)
{
	if (data->player.offset > -3000)
		data->player.offset -= 30;
}
