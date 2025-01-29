/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:17:11 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/29 20:01:00 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(int argc, char **argv)
{
	t_cub	*game;

	if (argc != 2)
		ft_error("ERROR: Invalid number of arguments");
	if (WIN_HEIGHT <= 0 || WIN_WIDTH <= 0)
		ft_error("ERROR: No valid measures");
	game = malloc(sizeof(t_cub));
	if (!game)
		return (1);
	ft_init_game(game);
	ft_check_file(game,argv[1]);
	ft_get_map(game, NULL, NULL);
	ft_check_map(game, -1, -1);
	//ft_init_mlx(game);
	//ft_cleanup(game);
	return (0);
}
