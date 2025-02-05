/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelope <albelope@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:01:31 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/05 11:50:22 by albelope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_coor	*malloc_coor(t_cub *game)
{
	t_coor	*coor;

	coor = ft_calloc(1, sizeof(t_coor));
	if (!coor)
		ft_error(game, 1, "Malloc failed");
	return (coor);
}

void ft_init_game(t_cub *game)
{
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->player)
		ft_error(game, 1, "Malloc failed");
	game->coor = malloc_coor(game);
	if (!game->coor)
		ft_error(game, 1, "Malloc failed");
	game->fd = -1;
	game->rays = ft_calloc(WIN_WIDTH, sizeof(t_ray));
	if (!game->rays)
		ft_error(game, 1, "Malloc failed for rays");
}