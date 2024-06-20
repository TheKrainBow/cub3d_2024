/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:48:21 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/20 18:27:37 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <limits.h>
# include <stdio.h>
# include <unistd.h>

# define KEY_ESC 65307
# define ERROR 1

# define WALL '1'
# define EMPTY '0'
# define PLAYER_NORTH 'N'
# define PLAYER_SOUTH 'S'
# define PLAYER_EAST 'E'
# define PLAYER_WEST 'W'

# define WRONG_TOKEN "Invalid token"
# define NOT_INT "Not a valid integer [0, 255]"
# define MISSING_TOKEN "Missing token"
# define UNEXPECTED_TOKEN "Unexpected token"
# define NO_MAP "No map found in file"
# define MULTIPLE_PLAYER "Map has more than one player"

typedef enum e_texture
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}					t_texture;

typedef struct s_color
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}					t_color;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			rotation;
	void			*texture;
}					t_player;

typedef struct s_parsing
{
	int				is_map;
	int				has_player;
	t_list			*lst_map;
}					t_parsing;

typedef struct s_textures
{
	void			*north;
	void			*south;
	void			*east;
	void			*west;
}					t_textures;

typedef struct s_data
{
	char			**map;
	int				map_x;
	int				map_y;
	void			*mlx;
	void			*win;
	void			*img;
	t_color			*draw;
	void			*img2;
	t_color			*draw2;
	t_player		player;
	t_color			floor;
	t_color			ceiling;
	t_parsing		parsing;
	t_textures		texture;
}					t_data;

int					parse_file(t_data *data, char *file);

#endif
