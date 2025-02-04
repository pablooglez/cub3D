/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelope <albelope@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:45:57 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/04 12:55:20 by albelope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*get_and_save_coor(t_cub *game, char *dst,
	char *coor, char *line)
{
	int		coor_len;
	char	*start;
	char	*path;

	if (!line || !*line || ft_is_whitespace_only(line))
		return (dst);
	coor_len = ft_strlen(coor);
	if (!dst && !ft_strncmp(line, coor, coor_len)
		&& (line[coor_len] == ' ' || line[coor_len] == '\t'))
	{
		start = (char *)(line + coor_len);
		while (*start == ' ' || *start == '\t')
			start++;
		path = ft_strdup(start);
		if (path && path[ft_strlen(path) - 1] == '\n')
			path[ft_strlen(path) - 1] = '\0';
		game->coor->n_coor++;
		return (path);
	}
	return (dst);
}

static void	ft_save_coor(t_cub *game, char *line)
{
	game->coor->north = get_and_save_coor(game,
		game->coor->north, "NO", line);
	game->coor->south = get_and_save_coor(game,
		game->coor->south, "SO", line);
	game->coor->west = get_and_save_coor(game,
		game->coor->west, "WE", line);
	game->coor->east = get_and_save_coor(game,
		game->coor->east, "EA", line);
	game->coor->floor = get_and_save_coor(game,
		game->coor->floor, "F", line);
	game->coor->ceiling = get_and_save_coor(game,
		game->coor->ceiling, "C", line);
}

static char	*append_map_line(char *result, char *line)
{
	char	*aux;

	aux = result;
	if (!aux)
		result = ft_strdup(line);
	else
	{
		result = ft_strjoin(aux, line);
		free(aux);
	}
	return (result);
}


void	ft_get_map(t_cub *game)
{
	char	*line;
	char	*result;

	result = NULL;
	while ((line = get_next_line(game->fd)))
	{
		if (!game->start_map)
		{
			ft_save_coor(game, line);
			if (line[0] == '1' || line[0] == '0')
				game->start_map = 1;
		}
		if (game->start_map && (line[0] == '1' || line[0] == '0'))
			result = append_map_line(result, line);
		free(line);
	}
	if (result)
	{
		game->map = ft_split(result, '\n');
		free(result);
	}
}

