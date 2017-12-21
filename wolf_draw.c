/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <skamoza@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 13:47:05 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/20 12:48:23 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	wolf_draw_floor_ceil(t_map *map, t_line line, int ceil, int y)
{
	t_point	floor;
	t_point	current_floor;
	double	dist;
	double	weight;

	y = y < 0 ? HEIGHT : y;
	floor.x = line.side ? line.map_x + line.wall_x : line.map_x;
	floor.y = line.side ? line.map_y : line.map_y + line.wall_x;
	floor.x = map->player.dir.x < 0 ? floor.x + 1.0 : floor.x;
	floor.y = map->player.dir.y < 0 ? floor.y + 1.0 : floor.x;
	while (y < HEIGHT)
	{
		dist = (double)HEIGHT / (2.0 * (double)y - (double)HEIGHT);
		weight = dist / line.dist;
		current_floor.x = weight * floor.x + (1.0 - weight) * map->player.pos.x;
		current_floor.y = weight * floor.y + (1.0 - weight) * map->player.pos.y;
		map->image.data[y * map->image.size_line / 4 + line.x] = 
		map->textures[1].data[(int)(floor.y * map->textures[1].h) % map->textures[1].h * map->textures[1].size_line / 4 + (int)(floor.x * map->textures[1].h) % map->textures[1].h];
		y++;
	}
}

static inline void	wolf_draw_wall(t_map *map, t_line line, int y, int draw_end)
{
	int		d;
	int		tex_y;

	while (y < draw_end)
	{
		d = y * 256 - HEIGHT * 128 + line.h * 128;
		tex_y = abs(((d * map->textures[line.tex].h) / line.h) / 256);
		map->image.data[y * map->image.size_line / 4 + line.x] =
		map->textures[line.tex].data[(int)(map->textures[line.tex].w *
													tex_y + line.tex_x)];
		y++;
	}
}

static inline void	wolf_draw_line(t_map *map, t_dda *dda, t_line line)
{
	int		draw_start;
	int		draw_end;

	line.h = ((double)HEIGHT / line.dist);
	line.dist = line.side ? (line.map_y - map->player.pos.y + (1.0 - dda->step.y) / 2.0) /
	dda->dir.y : (line.map_x - map->player.pos.x + (1.0 - dda->step.x) / 2.0) / dda->dir.x;
	draw_start = (-line.h + HEIGHT) / 2;
	draw_start = draw_start < 0 ? 0 : draw_start;
	draw_end = (line.h + HEIGHT) / 2;
	draw_end = draw_end >= HEIGHT ? HEIGHT - 1 : draw_end;
	line.wall_x = line.side ? map->player.pos.x + line.dist * dda->dir.x :
							map->player.pos.y + line.dist * dda->dir.y;
	line.wall_x -= floor(line.wall_x);
	line.tex_x = (int)(line.wall_x * (double)map->textures[line.tex].w);
	/*
	line.tex_x = (line.side == 0 && dda->dir.x < 0) || (line.side == 1 &&
	dda->dir.x > 0) ? map->textures[line.tex].w - line.tex_x - 1 : line.tex_x;
	*/
	line.x = dda->x;
	wolf_draw_wall(map, line, draw_start, draw_end);
	wolf_draw_floor_ceil(map, line, draw_start - 1, draw_end + 1);
}

static inline void	wolf_dda(t_map *map, t_dda *dda, int m_x, int m_y)
{
	t_line	line;

	while (1)
	{
		line.tex = 0;
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
		if (m_x < 0 || m_y < 0 || m_x >= map->map.w || m_y >= map->map.h
			|| (line.tex = map->map.data[m_y * map->map.size_line / 4 + m_x]))
			break ;
	}
	if (line.tex >= TEXTURES)
		wolf_error("invalid map, no such texture", map);
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
