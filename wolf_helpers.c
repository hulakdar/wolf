/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <skamoza@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:01:23 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/06 16:34:25 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			wolf_background(t_map *map, int ceiling, int floor)
{
	int cunt;
	int ceil;

	cunt = 0;
	ceil = WIDTH * HEIGHT;
	while (cunt < ceil >> 1)
	{
		map->image.data[cunt] = ceiling;
		cunt++;
	}
	while (cunt < ceil)
	{
		map->image.data[cunt] = floor;
		cunt++;
	}
}

inline int		wolf_get_sector(t_map *map, int m_y, int m_x)
{
	if (m_x < 0 || m_y < 0 || m_x >= map->map.w || m_y >= map->map.h)
		return (0);
	return (map->map.data[m_y * map->map.size_line / 4 + m_x]);
}

inline unsigned	wolf_get_tex(t_map *map, int m_y, int m_x, t_line line)
{
	t_sector sect;

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

int				wolf_get_texel(t_map *map, t_coord tex, int tex_c)
{
	return (map->tex[tex_c].data[tex.y * map->tex[tex_c].size_line / 4
		+ tex.x]);
}
