/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:05:27 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/30 16:58:13 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_mlx_init(t_cub *game)
{
	mlx_set_setting (MLX_STRETCH_IMAGE, true);
	game->init = mlx_init (WIN_WIDTH, WIN_HEIGHT, "cub3d", true);
	if (!game->init)
		ft_error(game, 1, "Failed to initialize MLX42");
	load_textures(game);
	//create_images(game);
	//put_textures(game);
}

void	load_textures(t_cub *game)
{
	game->coor->txt_north_i = mlx_load_png("./textures/wall_1.png");
	if (!game->coor->txt_north_i)
		ft_error(game, 1, "error loading texture: north");
	game->coor->txt_south_i = mlx_load_png("./textures/wall_2.png");
	if (!game->coor->txt_south_i)
		ft_error(game, 1, "error loading texture: south");
	game->coor->txt_east_i = mlx_load_png("./textures/wall_3.png");
	if (!game->coor->txt_east_i)
		ft_error(game, 1, "error loading texture: east");
	game->coor->txt_west_i = mlx_load_png("./textures/wall_4.png");
	if (!game->coor->txt_west_i)
		ft_error(game, 1, "error loading texture: west");
}