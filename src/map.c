/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:45:57 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/26 18:07:59 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*get_and_save_coor(t_cub *game, char *dst, char *coor, char *line)
{
	int	i;

	if (!line || !*line || line[0] == '\n')
		return (dst);
	i = ft_find_char_index(line);
	if (i && !ft_strncmp(line, coor, i))
	{
		if (dst)
		{
			ft_error(game, 1, "Duplicate texture");
		}
		game->coor.n_coor++;
		line += i;
		while (ft_isspace(*line))
			line++;
		return (ft_substr(line, 0, ft_strlen(line) - 1));
	}
	return (dst);
}

static int	ft_save_coor(t_cub *game, char *line, int *flag)
{
	int	i;

	i = ft_find_char_index(line);
	if (i && *line != '\n' && ft_strlen(line) > 0
		&& ft_strncmp(line, "NO", i)
		&& ft_strncmp(line, "SO", i)
		&& ft_strncmp(line, "WE", i)
		&& ft_strncmp(line, "EA", i)
		&& ft_strncmp(line, "F", i)
		&& ft_strncmp(line, "C", i)
		&& game->coor.n_coor < 6)
		(*flag) = 1;
	game->coor.north = get_and_save_coor(game, game->coor.north, "NO", line);
	game->coor.south = get_and_save_coor(game, game->coor.south, "SO", line);
	game->coor.west = get_and_save_coor(game, game->coor.west, "WE", line);
	game->coor.east = get_and_save_coor(game, game->coor.east, "EA", line);
	game->coor.floor = get_and_save_coor(game, game->coor.floor, "F", line);
	game->coor.ceiling = get_and_save_coor(game, game->coor.ceiling, "C", line);
	if (game->coor.n_coor >= 6)
		game->start_map = 1;
	return (game->start_map);
}

static int	process_line(t_cub *game, char *line, int *flag, int *i)
{
	if (game->start_map == 0 && ft_save_coor(game, line, flag))
		return (1);
	if (game->start_map == 1)
	{
		if (ft_is_whitespace_only(line))
			return (1);
		game->start_map = 2;
	}
	if (game->start_map == 2)
	{
		if (ft_is_whitespace_only(line))
			*flag = 9;
		else
		{
			if (line && line[0] && line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			game->map[(*i)++] = ft_strdup(line);
			if (*i == 1024)
				*flag = 8;
		}
	}
	free(line);
	return (0);
}

void	ft_get_map(t_cub *game)
{
	char	*line;
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	line = get_next_line(game->fd);
	while (line)
	{
		if (process_line(game, line, &flag, &i))
		{
			free(line);
			line = get_next_line(game->fd);
			continue ;
		}
		if (flag > 0)
			break ;
		line = get_next_line(game->fd);
	}
	game->map[i] = NULL;
	if (flag == 8)
		ft_error(game, 1, "Map too big");
	if (flag)
		ft_error(game, 1, "Invalid map");
}
