/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:01:31 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/30 14:45:51 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_coor	*malloc_coor(t_cub *game)
{
	t_coor	*coor;

	coor = malloc(sizeof(t_coor));
	if (!coor)
		ft_error(game, 1, "Malloc failed");
	coor->n_coor = 0;
	coor->north = NULL;
	coor->south = NULL;
	coor->east = NULL;
	coor->west = NULL;
	coor->floor = NULL;
	coor->ceiling = NULL;
	coor->north_i = NULL;
	coor->south_i = NULL;
	coor->east_i = NULL;
	coor->west_i = NULL;
	coor->t_ceiling = NULL;
	coor->t_floor = NULL;
	return (coor);
}

void ft_init_game(t_cub *game)
{
	game->mlx_init = NULL;
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		ft_error(game, 1, "Malloc failed");
	game->coor = malloc_coor(game);
	game->map = NULL;
	game->map_len = 0;
	game->start_map = 0;
	game->n_player = 0;
	game->fd = -1;
}