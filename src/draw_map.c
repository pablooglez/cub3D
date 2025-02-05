/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelope <albelope@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:43:28 by albelope          #+#    #+#             */
/*   Updated: 2025/02/05 11:43:49 by albelope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#define TILE_SIZE 64 // Tamaño de cada celda en la pantalla

void	draw_map(t_cub *game)
{
	int		y;
	int		x;
	mlx_image_t	*wall_texture;

	y = 0;
	while (game->map[y]) // Recorrer filas del mapa
	{
		x = 0;
		while (game->map[y][x]) // Recorrer columnas del mapa
		{
			if (game->map[y][x] == '1') // Si hay una pared
			{
				wall_texture = mlx_texture_to_image(game->init, game->coor->txt_north_i);
				if (wall_texture)
					mlx_image_to_window(game->init, wall_texture, x * TILE_SIZE, y * TILE_SIZE);
			}
			x++;
		}
		y++;
	}
}
