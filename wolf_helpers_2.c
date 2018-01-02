/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_helpers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 13:27:11 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/02 17:33:08 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

inline int		wolf_get_sector(t_map *map, int m_y, int m_x)
{
	if (m_x < 0 || m_y < 0 || m_x >= map->map.w || m_y >= map->map.h)
		return (0);
	return (map->map.data[m_y * map->map.size_line / 4 + m_x]);
}

inline unsigned wolf_get_tex(t_map *map, int m_y, int m_x, t_line line)
{
	t_sector sect;

	if (m_x < 0 || m_y < 0 || m_x >= map->map.w || m_y >= map->map.h)
		return (0);
	sect.tex = wolf_get_sector(map, m_y, m_x);
	if (sect.sect.is_wall)
	{
		if (line.side == 0 && line.ray_dir.x > 0.0)
			return (sect.sect.n);
		else if (line.side == 0 && line.ray_dir.x < 0.0)
			return (sect.sect.e);
		else if (line.side == 1 && line.ray_dir.y > 0.0)
			return (sect.sect.w);
		return (sect.sect.s);
	}
	else if (line.is_floor)
		return (sect.sect.w);
	return (sect.sect.s);
}

static inline t_point	wolf_find_floor(t_line line)
{
	t_point	floor;

	if (line.side == 0 && line.ray_dir.x > 0.0)
	{
		floor.x = line.map_x;
		floor.y = line.map_y + line.wall_x;
	}
	else if (line.side == 0 && line.ray_dir.x < 0.0)
	{
		floor.x = line.map_x + 1.0;
		floor.y = line.map_y + line.wall_x;
	}
	else if (line.side == 1 && line.ray_dir.y > 0.0)
	{
		floor.x = line.map_x + line.wall_x;
		floor.y = line.map_y;
	}
	else
	{
		floor.x = line.map_x + line.wall_x;
		floor.y = line.map_y + 1.0;
	}
	return (floor);
}

static inline t_coord	wolf_get_fc(t_map *map, int m_x, int m_y, t_line line)
{
	t_coord fc;
	
	line.is_floor = 1;
	fc.x = wolf_get_tex(map, m_y, m_x, line);
	line.is_floor = 0;
	fc.y = wolf_get_tex(map, m_y, m_x, line);
	return (fc);
}

void					wolf_draw_floor_ceil(t_map *map, t_line line, int y)
{
	t_point	floor;
	t_point	cur;
	t_point	dist;
	t_coord	tex;
	t_coord	tex_ceil;
	t_coord	tex_c;
	int		old;

	y = y < 0 ? HEIGHT : y;
	floor = wolf_find_floor(line);
	while (y < HEIGHT)
	{
		dist.x = (double)HEIGHT / (double)((y << 1) - HEIGHT);
		dist.y = dist.x / line.dist;
		cur.x = dist.y * floor.x + (1.0 - dist.y) * map->player.pos.x;
		cur.y = dist.y * floor.y + (1.0 - dist.y) * map->player.pos.y;
		tex_c = wolf_get_fc(map, (int)cur.x, (int)cur.y, line);
		tex_c.x = tex_c.x < 0 ? 0 : tex_c.x;
		tex_c.y = tex_c.y < 0 ? 0 : tex_c.y;
		tex.x = (int)(cur.x * map->tex[tex_c.x].w) % map->tex[tex_c.x].w;
		tex.y = (int)(cur.y * map->tex[tex_c.x].h) % map->tex[tex_c.x].h;
		tex_ceil.x = (int)(cur.x * map->tex[tex_c.y].w) % map->tex[tex_c.y].w;
		tex_ceil.y = (int)(cur.y * map->tex[tex_c.y].h) % map->tex[tex_c.y].h;
		old = map->image.data[y * map->image.size_line / 4 + line.x];
		map->image.data[y * map->image.size_line / 4 + line.x] =
		map->tex[tex_c.x].data[tex.y * map->tex[tex_c.x].size_line / 4 + tex.x];
		if (map->image.data[y * map->image.size_line / 4 + line.x] & 0xFF000000)
			map->image.data[y * map->image.size_line / 4 + line.x] = old;
		old = map->image.data[(HEIGHT - y) * map->image.size_line / 4 + line.x];
		map->image.data[(HEIGHT - y) * map->image.size_line / 4 + line.x] = 
		map->tex[tex_c.y].data[tex_ceil.y * map->tex[tex_c.y].size_line / 4 + tex_ceil.x];
		if (map->image.data[(HEIGHT - y) * map->image.size_line / 4 + line.x] & 0xFF000000)
			map->image.data[(HEIGHT - y) * map->image.size_line / 4 + line.x] = old;
		y++;
	}
}
