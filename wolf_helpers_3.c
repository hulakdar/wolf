/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_helpers_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 16:59:52 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/06 16:49:35 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		wolf_unpress(int keycode, t_map *map)
{
	if (keycode == BUTT_SHIFT_L || keycode == BUTT_SHIFT_R)
		map->buttons.strafe = 0;
	else if (keycode == BUTT_A || keycode == ARROW_LEFT)
		map->buttons.a = 0;
	else if (keycode == BUTT_D || keycode == ARROW_RIGHT)
		map->buttons.d = 0;
	else if (keycode == BUTT_W || keycode == ARROW_UP)
		map->buttons.w = 0;
	else if (keycode == BUTT_S || keycode == ARROW_DOWN)
		map->buttons.s = 0;
	return (0);
}

void	wolf_draw_minimap(t_map *map)
{
	mlx_put_image_to_window(map->mlx, map->window, map->minimap.ptr,
						WIDTH - map->minimap.w, 0);
}

int		wolf_is_wall(t_map *map, int m_x, int m_y)
{
	t_sector sect;

	sect.tex = wolf_get_sector(map, m_y, m_x);
	return (sect.sect.is_wall);
}

int		wolf_player(t_map *map)
{
	int			x;
	int			y;
	t_sector	sect;

	y = 0;
	while (y < map->map.h)
	{
		x = 0;
		while (x < map->map.w)
		{
			sect.tex = wolf_get_sector(map, y, x);
			if (!sect.sect.is_wall)
			{
				map->player.pos.x = (double)x + 0.5;
				map->player.pos.y = (double)y + 0.5;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
