/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:45:57 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/31 19:39:52 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*get_and_save_coor(t_cub *game, char *dst, char *coor, char *line)
{
	printf("%d\n",game->coor->n_coor);
	if (!dst && !ft_strncmp(line, coor, ft_find_char_index(line, ' ')))
	{
		game->coor->n_coor++;
		return (ft_substr(line, 0, ft_strlen(line) - 1));
	}
	if (dst)
		return (dst);
	return (NULL);
}

static void	ft_save_coor(t_cub *game, char *line, int *flag)
{
	if (*line != '\n' && ft_strlen(line) > 0
		&& ft_strncmp(line, "NO", ft_find_char_index(line, ' '))
		&& ft_strncmp(line, "SO", ft_find_char_index(line, ' '))
		&& ft_strncmp(line, "WE", ft_find_char_index(line, ' '))
		&& ft_strncmp(line, "EA", ft_find_char_index(line, ' '))
		&& ft_strncmp(line, "F", ft_find_char_index(line, ' '))
		&& ft_strncmp(line, "C", ft_find_char_index(line, ' '))
		&& game->coor->n_coor < 6)
		(*flag) = 1;
	game->coor->north = get_and_save_coor(game, game->coor->north, "NO", line);
	game->coor->south = get_and_save_coor(game, game->coor->south, "SO", line);
	game->coor->west = get_and_save_coor(game, game->coor->west, "WE", line);
	game->coor->east = get_and_save_coor(game, game->coor->east, "EA", line);
	game->coor->floor = get_and_save_coor(game, game->coor->floor, "F", line);
	game->coor->ceiling = get_and_save_coor(game, game->coor->ceiling, "C", line);
	if (game->coor->n_coor >= 6 && *line != '\n' && !ft_is_whitespace_only(line))
		game->start_map = 1;
}

static int	check_newline(char *line)
{
	int	i;
	
	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (0);
		i++;
	}
	return (1);	
}

void	ft_get_map(t_cub *game, char *aux, char *result)
{
	char	*line;
	int		flag;

	flag = 0;
	line = get_next_line(game->fd);
	while (line)
	{
		if (!game->start_map)
			ft_save_coor(game, line, &flag);
		else if (game->start_map)
		{
			aux = ft_strdup(result);
			result = ft_strjoin(aux, line);
			if (!check_newline(result))
			{
				printf("%s\n", result);
				flag = 1;
			}
		}
		free(line);
		line = get_next_line(game->fd);
	}
	if (result && !flag)
		game->map = ft_split(result, '\n');
	if (result)
		free(result);
	if (flag)
		ft_error(game, 1, "Unrecognized line");
}
