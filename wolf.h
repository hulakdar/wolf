/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:15:28 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/21 20:52:18 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#ifndef WOLF_H
# define WOLF_H
# define THREADS 4
# define TEXTURES 9
# define SPRITES 4
# define HEIGHT 700
# define WIDTH 700
# include <mlx.h>
# include <pthread.h>
# include <math.h>
# include "libft/includes/libft.h"

typedef unsigned char t_byte;
typedef union	u_color
{
	int			color;
	t_byte		channel[4];
}				t_color;
typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;
typedef struct	s_line
{
	int			tex;
	int			map_x;
	int			map_y;
	int			x;
	int			h;
	int			side;
	double		dist;
	double		wall_x;
	double		tex_x;
}				t_line;
typedef struct	s_dda
{
	t_point		dir;
	t_point		side_dist;
	t_point		d;
	t_point		step;
	int			pos_x;
	int			pos_y;
	int			x;
}				t_dda;
typedef struct	s_player
{
	t_point		pos;
	t_point		dir;
	t_point		plane;
}				t_player;
typedef struct	s_image
{
	void		*ptr;
	int			h;
	int			w;
	int			*data;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_image;
typedef struct	s_map
{
	t_image		map;
	t_image		image;
	t_image		textures[TEXTURES];
	t_image		sprites[SPRITES];
	t_player	player;
	void		*mlx;
	void		*window;
	char		buttons[300];
}				t_map;
void			wolf_error(char *error, t_map *parameter);
void			wolf_usage(void);
void			wolf_zoom(int keycode, int x, int y, t_map *map);
int				wolf_inter(double t, int offset);
void			wolf_draw(t_map *parameter);
void			wolf_rotate(t_player *player, double sign, double spd);
void			wolf_step(t_map *map, t_player *player, double spd);
void			wolf_background(t_map *map, int ceiling, int floor);
int				wolf_key(int keycode, t_map *parameter);
int				wolf_exit_x(t_map *parameter);
void			wolf_destruct(t_map *map);
#endif
