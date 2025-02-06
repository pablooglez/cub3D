/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:45:57 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/06 21:09:42 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*get_and_save_coor(t_cub *game, char *dst, char *coor, char *line)
{
	int	i;
	
	if (dst)
		return (dst);
	if (!line || !*line || line[0] == '\n') return (NULL);
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
	return (NULL);
}

static int	ft_save_coor(t_cub *game, char *line, int *flag)
{
	int i;

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

void	ft_get_map(t_cub *game, char *aux, char *result)
{
	char	*line;
	int		flag;
	int i = 0;

	(void) aux;
	(void) result;

	flag = 0;
	line = get_next_line(game->fd);
	while (line)
	{
		if (!game->start_map)
			if (ft_save_coor(game, line, &flag))
			{
				free(line);
				line = get_next_line(game->fd);
				continue;
			}
		if (game->start_map == 1) {
			if (ft_is_whitespace_only(line)) {
				free(line);
				line = get_next_line(game->fd);
				continue;
			}
			game->start_map = 2;
		}
		if (game->start_map == 2)
		{
			if (ft_is_whitespace_only(line))
				flag = 9;
			else
			{
				if (line && line[0] && line[ft_strlen(line) - 1] == '\n')
					line[ft_strlen(line) - 1] = '\0';
				game->map[i++] = ft_strdup(line);
				if (i == 1024)
					flag = 8;
			}
			
		}
		free(line);
		if (flag > 0)
			break;
		line = get_next_line(game->fd);
	}
	game->map[i] = NULL;
	if (result)
		free(result);
	if (flag == 8)
		ft_error(game, 1, "Tas pasao, tio");
	if (flag)
		ft_error(game, 1, "Unrecognized line");
}
