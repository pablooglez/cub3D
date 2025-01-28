/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:01:49 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/28 18:01:43 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_free_duplicate_map(t_cub *game)
{
	int	i;
	
	i = 0;
	if (game->map_copy[i])
	{
		while (game->map_copy[i])
		{
			free(game->map_copy[i]);
			i++;
		}
		free(game->map_copy[i]);
		game->map_copy = NULL;
	}
}

void ft_duplicate_map(t_cub *game)
{
	int	i;
	int	rows;
	
	if (!game->map || !game->coor)
		ft_error("Error: Original map not loaded correctly");
	rows = game->coor->map_rows;
	game->map_copy = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!game->map_copy)
		ft_error("Error: Unable to allocate memory for map copy");
	i = 0;
	while (i < rows)
	{
		game->map_copy[i] = ft_strdup(game->map[i]);
		if (!game->map_copy[i])
			ft_error("Error: Could not duplicate a map row");
		i++;
	}
	game->map_copy[i] = NULL;
}

void	flood_fill(t_cub *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->coor->map_cols || y >= game->coor->map_rows)
	{
		printf("Error: Map not closed at (%d, %d)\n", x, y);
		ft_error("Error: Map not closed");
	}
	printf("Filling cell at (%d, %d)\n", x, y);
	if (game->map_copy[y][x] == '1' || game->map[y][x] == 'X')
		return ;
	game->map_copy[y][x] = 'X';
	flood_fill(game, x + 1, y);
	flood_fill(game, x - 1, y);
	flood_fill(game, x, y + 1);
	flood_fill(game, x, y - 1);
}