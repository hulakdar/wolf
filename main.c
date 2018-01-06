/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <skamoza@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 13:30:33 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/06 19:39:39 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	wolf_hooks(t_map *map)
{
	mlx_hook(map->window, 2, 1L, wolf_key, map);
	mlx_hook(map->window, 3, 1L << 1, wolf_unpress, map);
	mlx_hook(map->window, 17, 1L << 17, wolf_exit_x, map);
	mlx_expose_hook(map->window, (int (*)())wolf_draw, map);
	mlx_loop_hook(map->mlx, (int (*)())wolf_loop, map);
	mlx_do_key_autorepeatoff(map->mlx);
	map->buttons.w = 0;
	map->buttons.s = 0;
	map->buttons.d = 0;
	map->buttons.a = 0;
	map->buttons.strafe = 0;
	map->buttons.gun_fire = 0;
}

void	wolf_open(void *mlx, t_image *image, char *map_name)
{
	if (!(image->ptr = mlx_xpm_file_to_image(mlx, map_name,
					&image->w, &image->h)))
		wolf_error(map_name, NULL);
	image->data = (int *)mlx_get_data_addr(image->ptr, &image->bits_per_pixel,
					&image->size_line, &image->endian);
}

void	wolf_init(t_map *map, char *map_name)
{
	static	char	*textures[] = {"tex/bg.xpm", "tex/fb.xpm",
		"tex/bricks.xpm", "tex/eagle.xpm", "tex/sand_bricks.xpm",
		"tex/white_bricks.xpm", "tex/wood.xpm", "tex/mossy.xpm",
		"tex/bluestone.xpm", "tex/greystone.xpm", "tex/metal.xpm"};
	int				cunt;

	if (!(map->mlx = mlx_init()))
		wolf_error("Something went completely wrong", NULL);
	wolf_open(map->mlx, &map->map, map_name);
	if (!(map->window = mlx_new_window(map->mlx, WIDTH, HEIGHT, "WOLF3D")))
		wolf_error("Something went completely wrong", NULL);
	cunt = -1;
	while (++cunt < TEXTURES)
		wolf_open(map->mlx, &map->tex[cunt], textures[cunt]);
	map->player.dir.x = 1.0;
	map->player.dir.y = 0.0;
	map->player.plane.x = 0.0;
	map->player.plane.y = 0.66;
	map->buttons.strafe = 0;
	wolf_hooks(map);
}

int		main(int argc, char **argv)
{
	t_map		map;
	int			cunt;
	t_sector	sect;

	if (argc != 2)
		wolf_usage();
	wolf_init(&map, argv[1]);
	cunt = 0;
	while (cunt < map.map.h * map.map.w)
	{
		sect.tex = map.map.data[cunt];
		if (sect.sect.n >= TEXTURES || sect.sect.e >= TEXTURES ||
				sect.sect.e >= TEXTURES || sect.sect.e >= TEXTURES)
			wolf_error("Invalid map, no such texture", NULL);
		cunt++;
	}
	if (!wolf_player(&map))
		wolf_error("Invalid map, the player is nowhere to put", NULL);
	map.image.ptr = mlx_new_image(map.mlx, WIDTH, HEIGHT);
	map.image.data = (int *)mlx_get_data_addr(map.image.ptr,
		&map.image.bits_per_pixel, &map.image.size_line, &map.image.endian);
	wolf_open(map.mlx, &map.hud, "hud.xpm");
	wolf_open(map.mlx, &map.gun, "gun.xpm");
	wolf_open(map.mlx, &map.gun_fire, "gun_fire.xpm");
	mlx_loop(map.mlx);
}
