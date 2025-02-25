/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:06:28 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/19 21:35:06 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_check_file(t_cub *game, char *argv)
{
	char	*archive;
	char	*backslash;

	archive = ft_strrchr(argv, '.');
	backslash = ft_strrchr(argv, '/');
	if (backslash && (!ft_strcmp (&backslash[1], ".cub")
			|| backslash[1] == '.'))
		ft_error(game, 1, "Can't have hidden files");
	if (!archive || ft_strcmp(archive, ".cub"))
		return (ft_error(game, 1, "Incorrect Extension"));
	if (ft_strlen(archive) == ft_strlen(argv))
		ft_error(game, 1, "Can't have hidden files");
	game->fd = open(argv, O_RDONLY);
	if (game->fd < 0)
		return (ft_error(game, 1, "Can't open file"));
}
