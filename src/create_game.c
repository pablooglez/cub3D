/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelope <albelope@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:05:27 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/05 12:40:44 by albelope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	load_textures(t_cub *game)
{
	game->coor->txt_north_i = mlx_load_png(game->coor->north);
	if (!game->coor->txt_north_i)
		ft_error(game, 1, "Error cargando textura: North");
	game->coor->txt_south_i = mlx_load_png(game->coor->south);
	if (!game->coor->txt_south_i)
		ft_error(game, 1, "Error cargando textura: South");
	game->coor->txt_east_i = mlx_load_png(game->coor->east);
	if (!game->coor->txt_east_i)
		ft_error(game, 1, "Error cargando textura: East");
	game->coor->txt_west_i = mlx_load_png(game->coor->west);
	if (!game->coor->txt_west_i)
		ft_error(game, 1, "Error cargando textura: West");
	printf("Texturas cargadas correctamente\n");
}

void	update_game(void *param)
{
	t_cub *game;

	game = (t_cub *)param;
	cast_rays(game);
}


void	ft_mlx_init(t_cub *game)
{
	mlx_set_setting (MLX_STRETCH_IMAGE, true);
	game->init = mlx_init (WIN_WIDTH, WIN_HEIGHT, "cub3d", true);
	if (!game->init)
		ft_error(game, 1, "Failed to initialize MLX42");
	load_textures(game);
	//draw_map(game);
	game->img_window = mlx_new_image(game->init, WIN_WIDTH, WIN_HEIGHT);
	if(!game->img_window)
		ft_error(game, 1, "Failed to create new image");
	mlx_loop_hook(game->init, update_game, game);
	if (mlx_image_to_window(game->init, game->img_window, 0, 0) < 0)
		ft_error(game, 1, "Failed to put image to window");
	mlx_loop(game->init);
	//create_images(game);
	//put_textures(game);
}
