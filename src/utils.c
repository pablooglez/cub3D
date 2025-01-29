/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:53:44 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/29 19:48:07 by pablogon         ###   ########.fr       */
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

int	ft_find_char_index(char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (c == '\0' && s[i] == '\0')
		return (i);
	return (0);
}

int	ft_is_whitespace_only(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && (line[i] < 9 || line[i] > 13))
			return (0);
		i++;
	}
	return (1);
}