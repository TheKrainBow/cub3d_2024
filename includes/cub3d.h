/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:48:21 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/01 18:57:32 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>

# define _USE_MATH_DEFINES

# define KEY_ESC 65307
# define ERROR 1
# define VALID 0
# define PI 3.14159265358979323846264338327950288

# define MOVE_STEP '1.0'
# define WALL '1'
# define EMPTY '0'
# define PLAYER_NORTH 'N'
# define PLAYER_SOUTH 'S'
# define PLAYER_EAST 'E'
# define PLAYER_WEST 'W'

# define WIN_X 1000
# define WIN_Y 580
//# define WIN_X 850
//# define WIN_Y 480
# define FOV 60
# define MAP_SCALE 15

# define WRONG_TOKEN "Invalid token"
# define NOT_INT "Not a valid integer [0, 255]"
# define MISSING_TOKEN "Missing token"
# define MISSING_COLOR "Missing a color"
# define UNEXPECTED_TOKEN "Unexpected token"
# define NO_MAP "No map found in file"
# define MULTIPLE_PLAYER "Map has more than one player"
# define FLOOR_DEFINED "Floor color is already defined"
# define CEILING_DEFINED "Ceiling color is already defined"
# define TEXTURE_DEFINED "Texture is already defined"

typedef enum e_key_code
{
	A_KEY = 113,
	Q_KEY = 97,
	S_KEY = 115,
	D_KEY = 100,
	Z_KEY = 119,
	W_KEY = 122,
	CLOSE_ICON = 17,
	ESC_KEY = 53,
	KEY_RELEASE = 3,
	LEFT_ARROW_KEY = 123,
	RIGHT_ARROW_KEY = 124,
	DOWN_ARROW_KEY = 125,
	UP_ARROW_KEY = 126
}			t_key_code;

typedef enum e_wall
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	NONE
}					t_wall;

typedef struct s_point
{
	int				x;
	int				y;
}				t_point;

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
	double			offset;
	void			*texture;
}					t_player;

typedef struct s_parsing
{
	int				is_map;
	int				has_player;
	t_list			*lst_map;
}					t_parsing;

typedef struct s_texture
{
	void		*ptr;
	char		*path;
	t_color		*draw;
	int			sizex;
	int			sizey;
}				t_texture;

typedef struct s_ray
{
	double			x;
	double			y;
	double			dist;
	double			angle;
	double			dirx;
	double			diry;
	double			distx;
	double			disty;
	double			stepx;
	double			stepy;
	double			deltax;
	double			deltay;
	double			impactx;
	double			impacty;
	int				side;
	t_wall			wall_type;
}					t_ray;

typedef struct s_input
{
	int				forward;
	int				backward;
	int				left;
	int				right;
	int				rot_left;
	int				rot_right;
	int				rot_up;
	int				rot_down;
	int				allow_mouse;
	int				has_map;
}				t_input;

typedef struct s_data
{
	char			**map;
	int				map_scale;
	int				map_x;
	int				map_y;
	void			*mlx;
	void			*win_map;
	void			*img_map;
	t_color			*draw_map;
	void			*win;
	void			*img;
	t_color			*draw;
	void			*img2;
	t_color			*draw2;
	t_player		player;
	int				has_floor;
	t_color			floor;
	int				has_ceiling;
	t_color			ceiling;
	t_parsing		parsing;
	t_texture		texture[4];
	t_ray			*ray;
	t_input			inputs;
}					t_data;

void				toggle_mouse(t_data *data);
int					parse_file(t_data *data, char *file);

void				calculate_img(t_data *data);
void				print_map(t_data *data);

/*	input.c	*/
int					key_press(int key_code, t_data *data);
int					key_up(int key_code, t_data *data);
int					mouse_hook(int x, int y, t_data *data);
int					key_press_bonus(int key_code, t_data *data);
/*	move.c	*/
void				ft_move_up(t_data *data);
void				ft_move_down(t_data *data);
void				ft_move_left(t_data *data);
void				ft_move_right(t_data *data);

int					line_error(char *line, char *error);
int					find_player(t_data *data);
int					parse_map_line(t_data *data, char *line);
int					parse_map(t_data *data);
int					is_map_token(char c);
int					parse_color_line(t_data *data, char *line);
int					parse_texture_line(t_data *data, char *line, t_wall type);
double				deg_to_rad(double angle);
double				parse_rotation(int c);
int					is_player(int c);
int					find_player(t_data *data);
void				draw_point(t_data *data, int x, int y, t_color color);
void				draw_map(t_data *data);
void				draw_map_point(t_data *data, int x, int y, t_color color);
void				display_ray(int x, double angle, t_data *data);
t_point				point(int x, int y);
t_color				color(unsigned char r, unsigned char g, unsigned char b);
/*	turn.c	*/
void				ft_turn_left(t_data *data);
void				ft_turn_right(t_data *data);
void				ft_turn_down(t_data *data);
void				ft_turn_up(t_data *data);
/* mlx.c */

double				fix_angle(double angle);
t_color				get_texture_color(int y, double height,
						double angle, t_data *data);
void				mlx_destroy(t_data *data);
int					start_mlx(t_data *data);
char				*texture_to_str(t_wall texture);

void				draw_point(t_data *data, int x, int y, t_color color);
void				draw_map_point(t_data *data, int x, int y, t_color color);
int					toggle_map(t_data *data);
double				fix_angle(double angle);
int					ft_abs(int x);

#endif
