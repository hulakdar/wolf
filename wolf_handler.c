/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:58:02 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/06 19:39:41 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	wolf_destruct(t_map *map)
{
	int cunt;

	cunt = -1;
	while (++cunt < TEXTURES)
		mlx_destroy_image(map->mlx, map->tex[cunt].ptr);
	cunt = -1;
	mlx_destroy_image(map->mlx, map->map.ptr);
	mlx_destroy_image(map->mlx, map->gun.ptr);
	mlx_destroy_image(map->mlx, map->gun_fire.ptr);
	mlx_destroy_image(map->mlx, map->hud.ptr);
	mlx_destroy_window(map->mlx, map->window);
	mlx_do_key_autorepeaton(map->mlx);
}

void	wolf_error(char *error, t_map *parameter)
{
	ft_putendl(error);
	if (parameter)
		wolf_destruct(parameter);
	exit(0);
}

void	wolf_usage(void)
{
	ft_putendl("usage: ./wolf map_file");
	exit(0);
}

int		wolf_key(int keycode, t_map *map)
{
	if (keycode == BUTT_ESC)
		wolf_exit_x(map);
	else if (keycode == BUTT_SHIFT_L || keycode == BUTT_SHIFT_R)
		map->buttons.strafe = 1;
	else if (keycode == BUTT_A || keycode == ARROW_LEFT)
		map->buttons.a = 1;
	else if (keycode == BUTT_D || keycode == ARROW_RIGHT)
		map->buttons.d = 1;
	else if (keycode == BUTT_W || keycode == ARROW_UP)
		map->buttons.w = 1;
	else if (keycode == BUTT_S || keycode == ARROW_DOWN)
		map->buttons.s = 1;
	else if (keycode == BUTT_SPACE && !map->buttons.gun_fire)
		map->buttons.gun_fire = 15;
	return (0);
}

int		wolf_exit_x(t_map *parameter)
{
	wolf_destruct(parameter);
	exit(0);
	return (0);
}
