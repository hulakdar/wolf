/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <skamoza@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 13:47:05 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/02 17:07:42 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static inline void	wolf_draw_wall(t_map *map, t_line line, int y, int draw_end)
{
	int		d;
	int		old;
	int		tex_y;

	while (y < draw_end)
	{
		d = y * 256 - HEIGHT * 128 + line.h * 128;
		tex_y = abs(((d * map->tex[line.tex].h) / line.h) / 256);
		old = map->image.data[y * map->image.size_line / 4 + line.x];
		map->image.data[y * map->image.size_line / 4 + line.x] =
		map->tex[line.tex].data[
		(int)(map->tex[line.tex].w * tex_y + line.tex_x)];
		if (map->image.data[y * map->image.size_line / 4 + line.x] & 0xFF000000)
			map->image.data[y * map->image.size_line / 4 + line.x] = old;
		y++;
	}
}

static inline void	wolf_draw_line(t_map *map, t_dda *dda, t_line line)
{
	int		draw_start;
	int		draw_end;

	line.dist = line.side ? (line.map_y - map->player.pos.y + (1.0 -
	dda->step.y) / 2.0) / dda->dir.y : (line.map_x - map->player.pos.x
	+ (1.0 - dda->step.x) / 2.0) / dda->dir.x;
	line.h = ((double)HEIGHT / line.dist);
	draw_start = (-line.h + HEIGHT) / 2;
	draw_start = draw_start < 0 ? 0 : draw_start;
	draw_end = (line.h + HEIGHT) / 2;
	draw_end = draw_end >= HEIGHT ? HEIGHT - 1 : draw_end;
	line.wall_x = line.side ? map->player.pos.x + line.dist * dda->dir.x :
							map->player.pos.y + line.dist * dda->dir.y;
	line.wall_x -= floor(line.wall_x);
	line.x = dda->x;
	line.is_floor = 0;
	line.tex = wolf_get_tex(map, line.map_x, line.map_y, line);
	line.tex_x = (int)(line.wall_x * (double)map->tex[line.tex].w);
	line.ray_dir = dda->dir;
	wolf_draw_wall(map, line, draw_start, draw_end);
	wolf_draw_floor_ceil(map, line, draw_end);
}

static inline void	wolf_dda(t_map *map, t_dda *dda, int m_x, int m_y)
{
	t_line	line;

	while (1)
	{
		line.sector.tex = 0;
		if (dda->side_dist.x < dda->side_dist.y && !(line.side = 0))
		{
			dda->side_dist.x += dda->d.x;
			m_x += dda->step.x;
		}
		else if ((line.side = 1))
		{
			dda->side_dist.y += dda->d.y;
			m_y += dda->step.y;
		}
		if ((line.sector.tex = wolf_get_sector(map, m_y, m_x)) == 0 ||
												line.sector.sect.is_wall)
			break ;
	}
	line.map_x = m_x;
	line.map_y = m_y;
	wolf_draw_line(map, dda, line);
}

static inline void	wolf_dda_prepare(t_map *map, t_dda *dda, double camera_x)
{
	dda->dir.x = map->player.dir.x + map->player.plane.x * camera_x;
	dda->dir.y = map->player.dir.y + map->player.plane.y * camera_x;
	dda->d.x = sqrt(1 + (dda->dir.y * dda->dir.y) / (dda->dir.x * dda->dir.x));
	dda->d.y = sqrt(1 + (dda->dir.x * dda->dir.x) / (dda->dir.y * dda->dir.y));
	dda->step.x = dda->dir.x < 0.0 ? -1 : 1;
	dda->side_dist.x = dda->dir.x < 0 ?
		map->player.pos.x - dda->pos_x : dda->pos_x + 1.0 - map->player.pos.x;
	dda->step.y = dda->dir.y < 0.0 ? -1 : 1;
	dda->side_dist.x *= dda->d.x;
	dda->side_dist.y = dda->dir.y < 0 ?
		map->player.pos.y - dda->pos_y : dda->pos_y + 1.0 - map->player.pos.y;
	dda->side_dist.y *= dda->d.y;
}

void				wolf_draw(t_map *map)
{
	int			x;
	t_dda		dda;
	double		camera_x;
	
	wolf_background(map, 0x505050, 0x808080);
	x = 0;
	dda.pos_x = (int)map->player.pos.x;
	dda.pos_y = (int)map->player.pos.y;
	while (x < WIDTH)
	{
		dda.x = x;
		camera_x = 2 * x / (double)WIDTH - 1.0;
		wolf_dda_prepare(map, &dda, camera_x);
		wolf_dda(map, &dda, dda.pos_x, dda.pos_y);
		x++;
	}
	mlx_put_image_to_window(map->mlx, map->window, map->image.ptr, 0 , 0);
}
