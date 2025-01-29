/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:42:15 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/29 16:55:57 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_check_file(t_cub *game, char *argv)
{
	char	*archive_name;
	char	*backslash;

	archive_name = ft_strrchr(argv, '.');
	backslash = ft_strrchr(argv, '/');

	if (backslash && (!ft_strcmp (&backslash[1], ".cub")
	|| backslash[1] == '.'))
		ft_error("ERROR: Can't have hidden files");
	if (ft_strcmp(archive_name, ".cub"))
		return (ft_error("ERROR: Incorrect Extension"));
	if (ft_strlen(archive_name) == ft_strlen(argv))
		ft_error("ERROR: Can't have hidden files");
	game->fd = open(argv, O_RDONLY);
	if (game->fd < 0)
		return (ft_error("ERROR: Can't open file"));
}
