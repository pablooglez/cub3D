/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:42:15 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/23 19:30:19 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_check_map_closed(t_cub *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[0][j])
	{
		if (game->map[0][j] != '1' && game->map[0][j] != ' ')
			return (0);
		j++;
	}
	j = 0;
	while (game->map[game->coor->map_rows - 1][j])
	{
		if (game->map[game->coor->map_rows - 1][j] != '1' && game->map[game->coor->map_rows - 1][j] != ' ')
			return (0);
		j++;
	}
	while (i < game->coor->map_rows)
	{
		if (game->map[i][0] != '1' && game->map[i][0] != ' ')
			return (0);
		int	len = ft_strlen_cub3d(game->map[i]);
		if (game->map[i][len - 1] != '1' && game->map[i][len - 1] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_valid_characters(t_cub *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			c = game->map[i][j];
			if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_file(char *str)
{
	int		len;

	remove_newline(str);
	len = ft_strlen_cub3d(str);
	if (len > 4 && ft_strncmp(&str[len - 4], ".cub", 4) == 0)
	{
		if (access(str, F_OK) == 0)
			return (1);
	}
	return (0);
}
