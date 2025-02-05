/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:03:11 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/05 18:58:15 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_textures(t_coor *coor)
{
	if (coor->txt_north_i)
		mlx_delete_texture(coor->txt_north_i);
	if (coor->txt_south_i)
		mlx_delete_texture(coor->txt_south_i);
	if (coor->txt_east_i)
		mlx_delete_texture(coor->txt_east_i);
	if (coor->txt_west_i)
		mlx_delete_texture(coor->txt_west_i);
}

void	free_coor(t_coor *coor)
{
	if (coor->north)
		free(coor->north);
	if (coor->south)
		free(coor->south);
	if (coor->east)
		free(coor->east);
	if (coor->west)
		free(coor->west);
	if (coor->floor)
		free(coor->floor);
	if (coor->ceiling)
		free(coor->ceiling);
	free_textures(coor);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_game(t_cub *game)
{
	int i;

	i = -1;
	while (game->map[++i])
		free(game->map[i]);
	if (game->player)
		free(game->player);
	free_coor(&game->coor);
	if (game->fd != -1)
		close(game->fd);
	if (game->init)
		mlx_terminate(game->init);
	free(game);
}