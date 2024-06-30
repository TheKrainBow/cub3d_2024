/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:28:32 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/30 17:29:24 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture_line(t_data *data, char *line, t_wall type)
{
	int		i;
	void	**texture;

	texture = &data->texture[type].ptr;
	i = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	i += 2;
	while (ft_iswhitespace(line[i]))
		i++;
	*texture = ft_strdup(line + i);
	while (line[i] && !ft_iswhitespace(line[i]))
		i++;
	while (ft_iswhitespace(line[i]))
		i++;
	if (line[i])
		return (line_error(line, UNEXPECTED_TOKEN));
	return (0);
}
