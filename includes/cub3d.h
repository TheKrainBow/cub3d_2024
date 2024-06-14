/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:48:21 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/14 16:54:35 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"

# define KEY_ESC 65307

typedef struct s_color
{
}			t_color;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		rotation;
	void		*texture;
}				t_player;

typedef struct s_data
{
	char		**map;
	int			map_x;
	int			map_y;
	void		*mlx;
	void		*win;
	void		*img;
	t_color		*draw;
	void		*img2;
	t_color		*draw2;
	void		*text_no;
	void		*text_so;
	void		*text_ea;
	void		*text_we;
	t_player	*player;
	t_color		floor;
	t_color		ceiling;
}			t_data;

#endif
