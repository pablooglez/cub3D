/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:17:11 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/05 20:56:45 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(int argc, char **argv)
{
	t_cub	*game;

	if (argc != 2)
		ft_error(NULL, 0, "Invalid number of arguments");
	if (WIN_HEIGHT <= 0 || WIN_WIDTH <= 0)
		ft_error(NULL, 1, "No valid measures");
	game = ft_calloc(1, sizeof(t_cub));
	if (!game)
		return (1);
	ft_init_game(game);
	ft_check_file(game,argv[1]);
	ft_get_map(game, NULL, NULL);
	ft_check_color(game, game->coor.floor, &game->coor.t_floor);
	ft_check_color(game, game->coor.ceiling, &game->coor.t_ceiling);
	ft_check_map(game, -1, -1);
	ft_mlx_init(game);
	free_game(game);
	return (0);
}
