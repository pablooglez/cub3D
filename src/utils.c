/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:53:44 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/23 19:29:31 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void remove_newline(char *str)
{
	int	len;

	len = ft_strlen_cub3d(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

int	ft_strlen_cub3d(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

void ft_init_game(t_cub *game)
{
	game->init = NULL;
	game->img_window = NULL;
	game->fd = -1;
	game->map = NULL;
	game->coor = malloc(sizeof(t_coor));
	if (!game->coor)
		ft_error("Error: Failed to allocate memory for coor");
	game->coor->north = NULL;
	game->coor->south = NULL;
	game->coor->west = NULL;
	game->coor->east = NULL;
	game->coor->floor_color = (t_color){-1, -1, -1};
	game->coor->ceiling_color = (t_color){-1, -1, -1};
	game->coor->map_rows = 0;
	game->coor->map_cols = 0;
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		ft_error("Error: Failed to allocate memory for player");
	game->player->x = -1;
	game->player->y = -1;
	game->player->angle = 0;
	game->player->move_speed = P_SPEED;
	game->player->rot_speed = R_SPEED;
	game->n_player = 0;
}