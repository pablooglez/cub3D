/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelope <albelope@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:53:44 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/23 12:52:36 by albelope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	change_spaces(t_cub *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
			if (game->map[y][x] == ' ')
				game->map[y][x] = '1';
	}
}

int	ft_find_char_index(char *s)
{
	int		i;

	i = 0;
	while (s && s[i] && !ft_isspace(s[i]))
		i++;
	return (i);
}

int	ft_is_whitespace_only(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] != ' ' && (line[i] < 9 || line[i] > 13))
			return (0);
		i++;
	}
	return (1);
}

unsigned int	get_rgba(t_color *color)
{
	return ((color->r << 24) | (color->g << 16) | (color->b << 8) | 255);
}
