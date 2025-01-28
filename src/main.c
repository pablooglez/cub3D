/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:17:11 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/28 20:04:56 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_check_game(t_cub *game, char *file)
{
	if (!ft_check_file(file))
		ft_error("Error: Invalid file extension");
	ft_check_map_size(game, file);
	ft_create_map(game, file);
	/*ft_duplicate_map(game);
	ft_expand_game(game);
	ft_get_player_position(game);
	if (!ft_check_valid_characters(game))
		ft_error("Error: Characters not allowed");
	if (!ft_check_map_closed(game))
		ft_error("Error: The map is not surrounded by walls");
	flood_fill(game, game->player->x, game->player->y);
	if (!ft_check_access(game))
		ft_error("Error: No access to all map areas");*/
	return (1);
}

int main(int argc, char **argv)
{
	t_cub game;

	if (argc != 2)
		ft_error("ERROR: Invalid number of arguments");
	ft_init_game(&game);
	if (!ft_check_game(&game, argv[1]))
	{
		//ft_cleanup(&game);
		return (1);
	}
	/*ft_parsing(&game);
	ft_cleanup(&game);*/
	return (0);
}
