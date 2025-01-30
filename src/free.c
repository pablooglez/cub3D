/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:03:11 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/30 14:54:45 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_textures(t_coor *coor)
{
	if (coor->north_i)
		mlx_delete_texture(coor->north_i);
	if (coor->south_i)
		mlx_delete_texture(coor->south_i);
	if (coor->east_i)
		mlx_delete_texture(coor->east_i);
	if (coor->west_i)
		mlx_delete_texture(coor->west_i);
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
	if (coor->t_floor)
		free(coor->t_floor);
	if (coor->t_ceiling)
		free(coor->t_ceiling);
	free_textures(coor);
	if (coor)
		free(coor);
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
	if (game->map)
		free_array(game->map);
	if (game->player)
		free(game->player);
	if (game->coor)
		free_coor(game->coor);
	if (game->fd != -1)
		close(game->fd);
	if (game->mlx_init)
		mlx_terminate(game->mlx_init);
	free(game);
}