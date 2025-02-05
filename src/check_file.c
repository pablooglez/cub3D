/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelope <albelope@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:06:28 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/04 12:52:39 by albelope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_check_file(t_cub *game, char *argv)
{
	char	*archive;
	char	*backslash;

	archive = ft_strrchr(argv, '.');
	backslash = ft_strrchr(argv, '/');
	if (backslash && (!ft_strcmp(&backslash[1], ".cub")
			|| backslash[1] == '.'))
		ft_error(game, 1, "Hidden files are not allowed.");
	if (!archive || ft_strcmp(archive, ".cub") != 0)
		ft_error(game, 1, "Invalid file extension (.cub required).");
	if (ft_strlen(archive) == ft_strlen(argv))
		ft_error(game, 1, "Hidden files are not allowed.");
	game->fd = open(argv, O_RDONLY);
	if (game->fd < 0)
		ft_error(game, 1, "Cannot open file.");
}
