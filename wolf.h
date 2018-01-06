/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:15:28 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/06 19:24:30 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# define THREADS 16
# define TEXTURES 11
# define HEIGHT 1300
# define WIDTH 1300
# include <mlx.h>
# include <pthread.h>
# include <math.h>
# include "libft/includes/libft.h"
# ifdef __APPLE__
#  include "mac_key.h"
# else
#  include "linux_key.h"
# endif

typedef unsigned char	t_byte;
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
typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;
typedef struct	s_sect{
	unsigned s : 4;
	unsigned w : 4;
	unsigned e : 4;
	unsigned n : 4;
	unsigned is_wall : 8;
	unsigned buffer : 8;
}				t_sect;
typedef union	u_sector
{
	unsigned	tex;
	t_sect		sect;
}				t_sector;
typedef struct	s_line
{
	t_sector	sector;
	int			map_x;
	int			map_y;
	int			x;
	int			tex;
	int			h;
	unsigned	side : 1;
	unsigned	is_floor : 1;
	double		dist;
	double		wall_x;
	double		tex_x;
	t_point		ray_dir;
	t_point		floor;
	t_point		cur;
	t_point		distance;
	t_coord		texe;
	t_coord		tex_ceil;
	t_coord		tex_c;
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
typedef	struct	s_buttons
{
	unsigned	w : 1;
	unsigned	a : 1;
	unsigned	s : 1;
	unsigned	d : 1;
	unsigned	strafe : 1;
	unsigned	gun_fire : 4;
}				t_buttons;
typedef struct	s_map
{
	t_image		map;
	t_image		hud;
	t_image		gun;
	t_image		gun_fire;
	t_image		minimap;
	t_image		image;
	t_image		tex[TEXTURES];
	t_player	player;
	t_buttons	buttons;
	void		*mlx;
	void		*window;
}				t_map;
typedef	struct	s_thread
{
	t_map		*map;
	int			x;
	int			ceil;
}				t_thread;
void			wolf_error(char *error, t_map *parameter);
void			wolf_draw_floor_ceil(t_map *map, t_line line, int y);
void			wolf_usage(void);
int				wolf_mouse(int keycode, int x, int y, t_map *map);
int				wolf_is_wall(t_map *map, int m_y, int m_x);
int				wolf_inter(double t, int offset);
int				wolf_draw(t_map *parameter);
void			*wolf_thr(t_thread *parameter);
int				wolf_loop(t_map *parameter);
int				wolf_player(t_map *parameter);
int				wolf_get_sector(t_map *parameter, int x, int y);
int				wolf_get_texel(t_map *map, t_coord x, int y);
unsigned		wolf_get_tex(t_map *parameter, int x, int y, t_line line);
void			wolf_background(t_map *map, int ceiling, int floor);
int				wolf_key(int keycode, t_map *parameter);
int				wolf_unpress(int keycode, t_map *parameter);
int				wolf_exit_x(t_map *parameter);
void			wolf_destruct(t_map *map);
#endif
