/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:01:31 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/05 18:48:05 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void ft_init_game(t_cub *game)
{
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->player)
		ft_error(game, 1, "Malloc failed");
	game->fd = -1;
}