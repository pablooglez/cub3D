/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:05:27 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/06 22:26:36 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//templates

static unsigned int	get_rgba(t_color *color);

void fill_world_data(t_cub *game)
{
	int a;
    for (int i = 0; i < WIN_WIDTH; i++) {
        game->rays[i].column = i;
        game->rays[i].side = EAST;
		if (i < 400) a = 600;
		if (i >= 400 && i <= 800) { a++; game->rays[i].side = SOUTH; }
		if (i > 800 && i <= 900) game->rays[i].side = WEST;
		if (i > 900 && i <= 1200) a = 100;
		if (i > 1200) a = 1200;
        game->rays[i].length = a;
    }
}

void draw_wall(t_cub *game, int x, int y, int side) {
	uint32_t color;
	t_color w_color;
	
	if (side == NORTH) { w_color.r = 255; w_color.g = 0; w_color.b = 0; }
	if (side == SOUTH) { w_color.r = 0; w_color.g = 0; w_color.b = 255; }
	if (side == WEST) { w_color.r = 255; w_color.g = 255; w_color.b = 0; }
	if (side == EAST) { w_color.r = 0; w_color.g = 255; w_color.b = 0; }
	color = get_rgba(&w_color);
	mlx_put_pixel(game->img_window, x, y, color);
}

//templates


static unsigned int	get_rgba(t_color *color)
{
	return ((unsigned int)color->r << 24 | (unsigned int)color->g << 16
		| (unsigned int)color->b << 8 | 255);
}

void	put_textures(void *param)
{
	t_cub *game;

	game = (t_cub *) param;
	int i = 0;
	while (i < WIN_WIDTH) {
		int top = (WIN_HEIGHT / 2) - (game->rays[i].length / 2);
		int bottom = (WIN_HEIGHT / 2) + (game->rays[i].length - (game->rays[i].length / 2));
		int j = 0;
		while (j < WIN_HEIGHT) {
			if (j < top)
				mlx_put_pixel(game->img_window, i, j, get_rgba(&game->coor.t_ceiling));
			else if (j >= top && j <= bottom)
				draw_wall(game, i, j, game->rays[i].side);
			else if (j > bottom)
				mlx_put_pixel(game->img_window, i, j, get_rgba(&game->coor.t_floor));
			j++;
		}
		i++;
	}
	
}

void	load_textures(t_cub *game)
{
	game->coor.txt_north_i = mlx_load_png(game->coor.north);
	game->coor.txt_south_i = mlx_load_png(game->coor.south);
	game->coor.txt_west_i = mlx_load_png(game->coor.west);
	game->coor.txt_east_i = mlx_load_png(game->coor.east);
	
	if (!game->coor.txt_north_i || !game->coor.txt_south_i
		|| !game->coor.txt_west_i || !game->coor.txt_east_i)
		ft_error(game, 1, "Failed to load textures");
}

void	ft_mlx_init(t_cub *game)
{
	mlx_set_setting (MLX_STRETCH_IMAGE, true);
	game->init = mlx_init (WIN_WIDTH, WIN_HEIGHT, "cub3d", true);
	if (!game->init)
		ft_error(game, 1, "Failed to initialize MLX42");
	load_textures(game);
	game->img_window = mlx_new_image(game->init, WIN_WIDTH, WIN_HEIGHT);
	mlx_image_to_window(game->init, game->img_window, 0, 0);
	fill_world_data(game);
	mlx_loop_hook(game->init, put_textures, game);
	//mlx_key_hook(game->init, &ft_keymoves, game);
	mlx_loop(game->init);
}
