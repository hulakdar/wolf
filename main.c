/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <skamoza@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 13:30:33 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/02 17:46:13 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		wolf_mouse(int keycode, int x, int y, t_map *map)
{
	wolf_draw(map);
	return (0);
}

int		wolf_unfocus(t_map *map)
{
	int cunt;
	int ceil;

	cunt = -1;
	ceil = WIDTH * HEIGHT;
	while (++cunt < ceil)
	{
		map->image.data[cunt] >>= 1;
		map->image.data[cunt] &= 0x7f7f7f;
	}
	mlx_put_image_to_window(map->mlx, map->window, map->image.ptr, 0 , 0);
	mlx_string_put(map->mlx, map->window, 10, 20, 0xFF1010,"PAUSE");
	return (0);
}

int		wolf_focus(t_map *map)
{
	mlx_put_image_to_window(map->mlx, map->window, map->image.ptr, 0 , 0);
	return (0);
}

int		wolf_test(t_map *map)
{
	printf("N\n");
	return (0);
}

int		wolf_unpress(int keycode, t_map *map)
{
	if (keycode == 257)
		map->strafe = 0;
	return (0);
}

void	wolf_hooks(t_map *map)
{
	mlx_hook(map->window, 9, 1L, wolf_focus, map);
	mlx_hook(map->window, 10, 1L, wolf_unfocus, map);
	mlx_hook(map->window, 2, 1L, wolf_key, map);
	mlx_hook(map->window, 3, 1L<<1, wolf_unpress, map);
	mlx_hook(map->window, 17, 1L << 17, wolf_exit_x, map);
	mlx_hook(map->window, 11, 1L, wolf_test, map);
	mlx_mouse_hook(map->window, (int (*)())wolf_mouse, map);
	mlx_expose_hook(map->window, (int (*)())wolf_draw, map);
	/*
	mlx_loop_hook(map->window, (int (*)())wolf_test, map);
	*/
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
	static	char	*textures[] = {"tex/bg.xpm", "tex/fb.xpm", "tex/bricks.xpm",
		"tex/eagle.xpm", "tex/sand_bricks.xpm", "tex/white_bricks.xpm",
		"tex/wood.xpm", "tex/mossy.xpm", "tex/bluestone.xpm",
		"tex/greystone.xpm"};
	static	char	*sprites[] = {"sprites/books.xpm", "sprites/PDF.xpm",
		"sprites/hand_left.xpm", "sprites/half_clock.xpm"};
	int				cunt;

	if (!(map->mlx = mlx_init()))
		wolf_error("Something went completely wrong", NULL);
	wolf_open(map->mlx, &map->map, map_name);
	if (!(map->window = mlx_new_window(map->mlx, WIDTH, HEIGHT, "WOLF3D")))
		wolf_error("Something went completely wrong", NULL);
	cunt = -1;
	while (++cunt < TEXTURES)
		wolf_open(map->mlx, &map->tex[cunt], textures[cunt]);
	cunt = -1;
	while (++cunt < SPRITES)
		wolf_open(map->mlx, &map->sprites[cunt], sprites[cunt]);
	map->player.pos.x = 0.5;
	map->player.pos.y = 0.5;
	map->player.dir.x = -1.0;
	map->player.dir.y = 0.0;
	map->player.plane.x = 0.0;
	map->player.plane.y = 0.66;
	map->strafe = 0;
	wolf_hooks(map);
}

int		main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		wolf_usage();
	wolf_init(&map, argv[1]);
	for (int i = 0; i < 24 * 3; i++)
	{
		t_sector sect;
		sect.tex = map.map.data[i];
		if (sect.sect.n >= TEXTURES || sect.sect.e >= TEXTURES ||
				sect.sect.e >= TEXTURES || sect.sect.e >= TEXTURES)
		{
			wolf_error("Invalid map, no such texture", NULL);
		}
	}
	printf("\n");
	map.image.ptr = mlx_new_image(map.mlx, WIDTH, HEIGHT);
	map.image.data = (int *)mlx_get_data_addr(map.image.ptr,
		&map.image.bits_per_pixel, &map.image.size_line, &map.image.endian);
	mlx_loop(map.mlx);
}
