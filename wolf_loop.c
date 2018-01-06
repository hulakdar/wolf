/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 16:44:58 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/06 19:39:39 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static inline void	wolf_strafe(t_map *map, t_player *player, double speed)
{
	double	old;
	t_point new;
	t_point	new_pos;

	old = player->dir.x;
	new.x = player->dir.x * cos(M_PI_2) - player->dir.y * sin(M_PI_2);
	new.y = old * sin(M_PI_2) + player->dir.y * cos(M_PI_2);
	new_pos.x = player->pos.x + new.x * speed;
	new_pos.y = player->pos.y + new.y * speed;
	if (new_pos.x >= 0 && new_pos.x < map->map.w && player->pos.y >= 0 &&
	player->pos.y < map->map.h &&
	!wolf_is_wall(map, (int)new_pos.x, (int)player->pos.y))
		player->pos.x = new_pos.x;
	if (player->pos.x >= 0 && player->pos.x < map->map.w && new_pos.y >= 0 &&
	new_pos.y < map->map.h &&
	!wolf_is_wall(map, (int)player->pos.x, (int)new_pos.y))
		player->pos.y = new_pos.y;
}

static inline void	wolf_step(t_map *map, t_player *player, double speed)
{
	t_point	new_pos;

	new_pos.x = player->pos.x + player->dir.x * speed;
	new_pos.y = player->pos.y + player->dir.y * speed;
	if (new_pos.x >= 0 && new_pos.x < map->map.w && player->pos.y >= 0 &&
	player->pos.y < map->map.h &&
	!wolf_is_wall(map, (int)new_pos.x, (int)player->pos.y))
		player->pos.x = new_pos.x;
	if (player->pos.x >= 0 && player->pos.x < map->map.w && new_pos.y >= 0 &&
	new_pos.y < map->map.h &&
	!wolf_is_wall(map, (int)player->pos.x, (int)new_pos.y))
		player->pos.y = new_pos.y;
}

static inline void	wolf_rotate(t_player *player, double sign, double spd)
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

int					wolf_loop(t_map *map)
{
	if (map->buttons.w || map->buttons.s)
		wolf_step(map, &map->player, map->buttons.w ? 0.14 : -0.14);
	if (map->buttons.strafe && (map->buttons.a || map->buttons.d))
		wolf_strafe(map, &map->player, map->buttons.a ? -0.05 : 0.05);
	else if (map->buttons.a || map->buttons.d)
		wolf_rotate(&map->player, map->buttons.a ? -1.0 : 1.0, 0.07);
	if (map->buttons.gun_fire)
		map->buttons.gun_fire--;
	wolf_draw(map);
	return (0);
}
