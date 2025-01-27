/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:17:11 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/27 17:34:50 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_check_game(t_cub *game, char *file)
{
	if (!file)
		return (0);
	if (!ft_check_file(file))
		ft_error("Error: Invalid file extension");
	ft_load_game(game, file);
	if (!ft_check_valid_characters(game))
		ft_error("Error: Characters not allowed");
	if (!ft_check_map_closed(game))
		ft_error("Error: The map is not surrounded by walls");
	/*ft_duplicate_map(game);
	ft_get_player_position(game);
	if (game->player->x == -1 && game->player->y == -1)
		ft_error("Error: Player position not found");
	flood_fill(game, game->player->x, game->player->y);
	if (!ft_check_access(game))
		ft_error("Error: No access to all map areas");*/
	return (1);
}

int main(int argc, char **argv)
{
	t_cub game;

	if (argc == 2)
	{
		printf("Initializing game...\n");
		ft_init_game(&game);  // Inicializa la estructura

		printf("Checking game file...\n");
		if (!ft_check_game(&game, argv[1]))
		{
			printf("Game check failed.\n");
			return (1);  // Salir si la verificación falla
		}
		printf("File check passed.\n");

		printf("Loading game...\n");
		printf("Game loaded successfully.\n");

		printf("Checking valid characters...\n");
		if (!ft_check_valid_characters(&game))
		{
			printf("Error: Characters not allowed\n");
			return (1);  // Salir si la verificación falla
		}
		printf("Valid characters check passed.\n");

		printf("Checking if map is closed by walls...\n");
		if (!ft_check_map_closed(&game))
		{
			printf("Error: The map is not surrounded by walls\n");
			return (1);  // Salir si la verificación falla
		}
		printf("Map closed check passed.\n");

		printf("All checks up to ft_check_map_closed passed successfully!\n");

		// Limpieza (opcional, dependiendo de tu implementación)
		// ft_cleanup(&game);
	}
	else
		ft_error("ERROR: Invalid number of arguments");
	return (0);
}
