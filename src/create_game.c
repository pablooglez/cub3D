/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:05:27 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/30 19:35:24 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_mlx_init(t_cub *game)
{
	mlx_set_setting (MLX_STRETCH_IMAGE, true);
	game->init = mlx_init (WIN_WIDTH, WIN_HEIGHT, "cub3d", true);
	if (!game->init)
		ft_error(game, 1, "Failed to initialize MLX42");
	//load_textures(game);
	//create_images(game);
	//put_textures(game);
}
