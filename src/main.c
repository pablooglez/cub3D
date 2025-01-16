/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:17:11 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/16 21:12:39 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_check_game(t_cub *game, char *file)
{
	if (!ft_check_file(file))
		ft_error("Error: Invalid file extension");
	ft_init_game(game);
	if (!ft_check_map_size(game, file))
		ft_error("Error: Invalid map size");
	ft_load_game(game, file);
	if (!ft_check_correct_characters(game))
		ft_error("Error: Characters not allowed");
	if (!ft_check_walls(file))
		ft_error("Error: The map is not surrounded by walls");
	ft_duplicate_map(game);
	ft_get_player_position(game);
	if (game->player->x == -1 && game->player->y == -1)
		ft_error("Error: Player position not found");
	flood_fill(game, game->player->x, game->player->y);
	if (!ft_check_access(game))
		ft_error("Error: No access to all map areas");
}

int	main(int argc, char **argv)
{
	t_cub	*game;

	if (argc == 2)
	{
		ft_check_game(&game, argv[1]);
		//ft_mlx_init(&game);
		//ft_cleanup(&game);
	}
	else
		ft_error("ERROR: Invalid number of arguments");
	return (0);
}
