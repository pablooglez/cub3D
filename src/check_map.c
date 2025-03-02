/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:42:15 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/24 19:34:18 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	ft_check_char(t_cub *game, char current, char next)
{
	if (!ft_strchr("10NSWE ", current))
		return (ft_error(game, 1, "Invalid character on map."), 0);
	else if (current == '1' || current == ' ')
		return (1);
	else if (current == '0' && (!ft_strchr("10NSWE", next) || !next))
		return (ft_error(game, 1, "Invalid map."), 0);
	else if (ft_strchr("NSWE", current) && (!ft_strchr("10", next) || !next))
		return (ft_error(game, 1, "Invalid map."), 0);
	return (1);
}

static int	ft_check_walls(t_cub *game, int y, int x)
{
	if (ft_strchr("0NSWE", game->map[y][x]) && (y == 0 || !game->map[y - 1]))
		return (ft_error(game, 1, "Invalid map"), 0);
	else if (ft_strchr("0NSWE", game->map[y][x]) && !game->map[y + 1])
		return (ft_error(game, 1, "Invalid map."), 0);
	else if (ft_strchr("0NSWE", game->map[y][x])
		&& (x == 0 || !game->map[y][x - 1]))
		return (ft_error(game, 1, "Invalid map."), 0);
	else if (ft_strchr("0NSWE", game->map[y][x]) && !game->map[y][x + 1])
		return (ft_error(game, 1, "Invalid map."), 0);
	return (1);
}

void	fill_map_with_spaces(t_cub *game)
{
	size_t	max;
	int		y;
	char	*temp;

	y = -1;
	max = ft_strlen(game->map[0]);
	while (game->map[++y])
		if (ft_strlen(game->map[y]) > max)
			max = ft_strlen(game->map[y]);
	y = -1;
	while (game->map[++y])
	{
		while (ft_strlen(game->map[y]) < max)
		{
			temp = game->map[y];
			game->map[y] = ft_strjoin(game->map[y], " ");
			free(temp);
		}
	}
}

void	ft_check_map(t_cub *game, int y, int x)
{
	if (game->coor.n_coor != 6)
		ft_error (game, 1, "There is not a texture");
	if (!game->map[0])
		return (ft_error(game, 1, "There is not a map"));
	fill_map_with_spaces(game);
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			ft_check_walls(game, y, x);
			if (y >= 0 && x >= 0)
			{
				if (x > 0)
					ft_check_char(game, game->map[y][x], game->map[y][x - 1]);
				ft_check_char(game, game->map[y][x], game->map[y][x + 1]);
				if (y > 0)
					ft_check_char(game, game->map[y][x], game->map[y - 1][x]);
				if (game->map[y] && game->map[y + 1])
					ft_check_char(game, game->map[y][x], game->map[y + 1][x]);
			}
		}
	}
	change_spaces(game);
	initialize_player_position(game);
}
