/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <skamoza@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:01:23 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/21 20:50:40 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	wolf_step(t_map *map, t_player *player, double speed)
{
	t_point	new_pos;

	new_pos.x = player->pos.x + player->dir.x * speed;
	new_pos.y = player->pos.y + player->dir.y * speed;
	if (new_pos.x >= 0 && new_pos.x < map->map.w && player->pos.y >= 0 &&
	player->pos.y < map->map.h)
		player->pos.x = new_pos.x;
	/*
	   	&& !((map->map.data[(int)(player->pos.y *
	(map->map.size_line >> 2) + new_pos.x)]) & 0xFFFFFF))
	*/
	if (player->pos.x >= 0 && player->pos.x < map->map.w && new_pos.y >= 0 &&
	new_pos.y < map->map.h)
		player->pos.y = new_pos.y;
	/*
	!(map->map.data[(int)(new_pos.y *
	(map->map.size_line >> 2) + player->pos.x)]))
	*/
}

void	wolf_background(t_map *map, int ceiling, int floor)
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

void	wolf_rotate(t_player *player, double sign, double spd)
{
	double old;

	spd *= sign;
	old = player->dir.x;
	player->dir.x = player->dir.x * cos(spd) - player->dir.y * sin(spd);
	player->dir.y = old * sin(spd) + player->dir.y * cos(spd);
	old = player->plane.x;
	player->plane.x = player->plane.x * cos(spd) - player->plane.y * sin(spd);
	player->plane.y = old * sin(spd) + player->plane.y * cos(spd);
}

