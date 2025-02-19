/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:05:27 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/19 21:49:29 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	load_textures(t_cub *game)
{
	game->coor.txt_north_i = mlx_load_png(game->coor.north);
	game->coor.txt_south_i = mlx_load_png(game->coor.south);
	game->coor.txt_west_i = mlx_load_png(game->coor.west);
	game->coor.txt_east_i = mlx_load_png(game->coor.east);
	if (!game->coor.txt_north_i || !game->coor.txt_south_i
		|| !game->coor.txt_west_i || !game->coor.txt_east_i)
		ft_error(game, 1, "Failed to load textures");
	else
	{
		printf("texturas ok.\n");
		printf("north: %s\n", game->coor.north);
		printf("South: %s\n", game->coor.south);
		printf("West: %s\n", game->coor.west);
		printf("East: %s\n", game->coor.east);
	}
}

void	ft_mlx_init(t_cub *game)
{
	mlx_set_setting (MLX_STRETCH_IMAGE, true);
	game->init = mlx_init (WIN_WIDTH, WIN_HEIGHT, "cub3d", true);
	if (!game->init)
		ft_error(game, 1, "Failed to initialize MLX42");
	game->img_window = mlx_new_image(game->init, WIN_WIDTH, WIN_HEIGHT);
	mlx_image_to_window(game->init, game->img_window, 0, 0);
	load_textures(game);
	mlx_loop_hook(game->init, put_textures, game);
	mlx_key_hook(game->init, &ft_keymoves, game);
	mlx_loop_hook(game->init, ft_process_movement, game);
	mlx_loop(game->init);
}
