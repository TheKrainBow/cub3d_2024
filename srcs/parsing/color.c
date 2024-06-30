/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:27:23 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/30 17:28:10 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_color(char *line, int *i, unsigned char *color)
{
	int	tmp_color;

	while (ft_iswhitespace(line[*i]))
		(*i)++;
	if (!ft_isdigit(line[*i]))
		return (line_error(line, NOT_INT));
	*color = ft_atoi(line + *i);
	tmp_color = *color;
	if (tmp_color > 255)
		return (line_error(line, NOT_INT));
	while (ft_isdigit(line[*i]) || ft_iswhitespace(line[*i]))
		(*i)++;
	return (0);
}

int	parse_color_line(t_data *data, char *line)
{
	t_color	*color;
	int		i;

	i = 0;
	if (line[i] == 'F')
		color = &data->floor;
	else
		color = &data->ceiling;
	i++;
	if (parse_color(line, &i, &color->r) == ERROR)
		return (ERROR);
	if (line[i] != ',')
		return (line_error(line, MISSING_TOKEN));
	i++;
	if (parse_color(line, &i, &color->g) == ERROR)
		return (ERROR);
	if (line[i] != ',')
		return (line_error(line, MISSING_TOKEN));
	i++;
	if (parse_color(line, &i, &color->b) == ERROR)
		return (ERROR);
	if (line[i] != '\0')
		return (line_error(line, UNEXPECTED_TOKEN));
	return (0);
}
