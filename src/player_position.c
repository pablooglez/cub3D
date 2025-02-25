/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:33:21 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/24 19:36:29 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_player_view(t_player *player, char direction)
{
	if (direction == 'N')
		player->view = M_PI / 2;
	else if (direction == 'S')
		player->view = 3 * M_PI / 2;
	else if (direction == 'E')
		player->view = 0;
	else if (direction == 'W')
		player->view = M_PI;
}

static void	find_player_position(t_cub *game, int y, int x)
{
	if (ft_strchr("NSWE", game->map[y][x]))
	{
		game->player->x = x + 0.5;
		game->player->y = y + 0.5;
		set_player_view(game->player, game->map[y][x]);
		game->n_player++;
	}
}

void	initialize_player_position(t_cub *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			find_player_position(game, y, x);
		}
	}
	if (game->n_player != 1)
		ft_error(game, 1, "Invalid number of players.");
}
