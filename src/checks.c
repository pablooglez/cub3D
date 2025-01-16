/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:42:15 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/16 20:58:55 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_check_map_size(t_cub *game, char *file)
{
	int		fd;
	char	*line;
	int		len;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("Error: Could not open map file");
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (0);
	}
	len = ft_strlen_cub3d(line);
	while (line)
	{
		game->coor->map_rows++;
		free(line);
		line = get_next_line(fd);
		if (line && len != ft_strlen_cub3d(line))
			return (free(line), 0);
	}
	return (1);
}

int	ft_check_file(char *str)
{
	int	i;
	
	i = 0;
	if (ft_strlen(str) > 4)
	{
		while (str[i])
		{
			if (ft_strncmp(&str[i], ".cub\0", 5) == 0)
			{
				return (1);
			}
			i++;
		}
	}
	return (0);
}

