/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:58:02 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/26 18:28:47 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	wolf_destruct(t_map *map)
{
	int cunt;

	cunt = -1;
	while (++cunt < TEXTURES)
		mlx_destroy_image(map->mlx, map->textures[cunt].ptr);
	cunt = -1;
	while (++cunt < SPRITES)
		mlx_destroy_image(map->mlx, map->sprites[cunt].ptr);
	mlx_destroy_image(map->mlx, map->map.ptr);
	mlx_destroy_window(map->mlx, map->window);
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
	if (keycode == 53)
		wolf_exit_x(map);
	else if (keycode == 257)
		map->strafe = 1;
	else if (map->strafe && (keycode == 123 || keycode  == 124))
		wolf_strafe(map, &map->player, keycode == 123 ? 0.2 : -0.2);
	else if (keycode == 126 || keycode  == 125)
		wolf_step(map, &map->player, keycode == 126 ? 0.2 : -0.2);
	else if (keycode == 123 || keycode == 124)
		wolf_rotate(&map->player, keycode == 123 ? 1.0 : -1.0, 0.2);
	else
		printf("Keycode: %d\n", keycode);
	wolf_draw(map);
	return (0);
}

int		wolf_exit_x(t_map *parameter)
{
	wolf_destruct(parameter);
	exit(0);
	return (0);
}
