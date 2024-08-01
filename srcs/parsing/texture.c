/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:28:32 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/01 18:32:20 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture_line(t_data *data, char *line, t_wall type)
{
	int		i;
	char	**texture;

	if (data->texture[type].path)
		return (line_error(line, TEXTURE_DEFINED));
	texture = &data->texture[type].path;
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

char	*texture_to_str(t_wall texture)
{
	if (texture == NORTH)
		return ("north texture");
	if (texture == SOUTH)
		return ("south texture");
	if (texture == EAST)
		return ("east texture");
	if (texture == WEST)
		return ("west texture");
	return ("");
}
