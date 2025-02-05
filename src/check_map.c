/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelope <albelope@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:42:15 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/05 11:24:36 by albelope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	ft_check_walls(t_cub *game, int y, int x)
{
	if (!ft_strchr("10NSWE ", game->map[y][x]))
		ft_error(game, 1, "Caracter invalido en el mapa.");
	if (ft_strchr("0NSWE", game->map[y][x]))
	{
		if (y == 0 || y == game->map_len - 1)
			ft_error(game, 1, "Mapa abierto por arriba/abajo.");
		if (x == 0 || x == (int)ft_strlen(game->map[y]) - 1)
			ft_error(game, 1, "Mapa abierto en un lado.");
		if (game->map[y - 1][x] == ' ' || game->map[y + 1][x] == ' '
			|| game->map[y][x - 1] == ' ' || game->map[y][x + 1] == ' ')
			ft_error(game, 1, "Mapa no cerrado: hay un ' ' adyacente.");
	}
}

static void	initialize_player_position(t_cub *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (ft_strchr("NSWE", game->map[y][x]))
			{
				game->player->x = x + 0.5;
				game->player->y = y + 0.5;
				game->player->view = game->map[y][x];
				game->n_player++;
			}
			x++;
		}
		y++;
	}
	if (game->n_player != 1)
		ft_error(game, 1, "Numero de jugadores invalido (debe haber 1).");
}

void	ft_check_map(t_cub *game, int y, int x)
{
	(void)x;
	if (game->coor->n_coor != 6)
		ft_error(game, 1, "Falta alguna textura o color (deben ser 6).");
	if (!game->map)
		ft_error(game, 1, "No existe ningun mapa en game->map.");
	y = 0;
	while (game->map[y])
	{
		ft_check_walls(game, y, 0);
		x = 1;
		while (game->map[y][x])
		{
			ft_check_walls(game, y, x);
			x++;
		}
		y++;
	}
	game->map_len = y;
	initialize_player_position(game);
}
