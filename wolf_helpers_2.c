/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_helpers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 13:27:11 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/06 16:33:06 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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

static inline t_line	wolf_get_fc(t_map *map, t_line line)
{
	line.distance.y = line.distance.x / line.dist;
	line.cur.x = line.distance.y * line.floor.x + (1.0 - line.distance.y)
		* map->player.pos.x;
	line.cur.y = line.distance.y * line.floor.y + (1.0 - line.distance.y)
		* map->player.pos.y;
	line.is_floor = 1;
	line.tex_c.x = wolf_get_tex(map, (int)line.cur.y, (int)line.cur.x, line);
	line.is_floor = 0;
	line.tex_c.y = wolf_get_tex(map, (int)line.cur.y, (int)line.cur.x, line);
	line.tex_c.x = line.tex_c.x < 0 ? 0 : line.tex_c.x;
	line.tex_c.y = line.tex_c.y < 0 ? 0 : line.tex_c.y;
	line.texe.x = (int)(line.cur.x * map->tex[line.tex_c.x].w) %
		map->tex[line.tex_c.x].w;
	line.texe.y = (int)(line.cur.y * map->tex[line.tex_c.x].h) %
		map->tex[line.tex_c.x].h;
	line.tex_ceil.x = (int)(line.cur.x * map->tex[line.tex_c.y].w) %
		map->tex[line.tex_c.y].w;
	line.tex_ceil.y = (int)(line.cur.y * map->tex[line.tex_c.y].h) %
		map->tex[line.tex_c.y].h;
	return (line);
}

void					wolf_draw_floor_ceil(t_map *map, t_line line, int y)
{
	int		old;

	y = y < 0 ? HEIGHT : y;
	line.floor = wolf_find_floor(line);
	while (y < HEIGHT)
	{
		line.distance.x = (double)HEIGHT / (double)((y << 1) - HEIGHT);
		line = wolf_get_fc(map, line);
		old = map->image.data[y * map->image.size_line / 4 + line.x];
		map->image.data[y * map->image.size_line / 4 + line.x] =
			wolf_get_texel(map, line.texe, line.tex_c.x);
		if ((map->image.data[y * map->image.size_line / 4 + line.x]
			& 0xFF000000) || !line.tex_c.y)
			map->image.data[y * map->image.size_line / 4 + line.x] = old;
		old = map->image.data[(HEIGHT - y) * map->image.size_line / 4 + line.x];
		map->image.data[(HEIGHT - y) * map->image.size_line / 4 + line.x] =
			wolf_get_texel(map, line.tex_ceil, line.tex_c.y);
		if ((map->image.data[(HEIGHT - y) * map->image.size_line / 4 + line.x]
			& 0xFF000000) || !line.tex_c.x)
			map->image.data[(HEIGHT - y) *
				map->image.size_line / 4 + line.x] = old;
		y++;
	}
}

int						wolf_draw(t_map *map)
{
	int			x;
	int			i;
	pthread_t	thread[THREADS];
	t_thread	info[THREADS];

	wolf_background(map, 0x505050, 0x808080);
	x = 0;
	i = 0;
	while (i < THREADS)
	{
		info[i].map = map;
		info[i].x = x;
		x += (WIDTH / THREADS);
		info[i].ceil = x;
		pthread_create(&(thread[i]), NULL, (void *(*)())wolf_thr, &(info[i]));
		i++;
	}
	while (i-- > 0)
		pthread_join(thread[i], NULL);
	mlx_put_image_to_window(map->mlx, map->window, map->image.ptr, 0, 0);
	return (1);
}
