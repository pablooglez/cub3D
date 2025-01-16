/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:01:49 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/16 20:05:42 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_get_player_position(t_cub *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->coor->map_rows)
	{
		x = 0;
		while (x < game->coor->map_cols)
		{
			if (ft_strchr("NSEW", game->map[y][x]))
			{
				game->player->x = x + 0.5;
				game->player->y = y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
}