/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:03:11 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/07 19:51:07 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_textures(t_coor *coor)						// Libera las texturas almacenadas en la estructura t_coor.
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

void	free_coor(t_coor *coor)							// Libera la memoria de los archivos de texturas y del techo/suelo.
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
	free_textures(coor);								// Llama a la función para liberar texturas.
}

void	free_array(char **array)						// Libera un array de strings (char **).
{
	int	i;

	if (!array)											// Si el array es NULL, no hace nada.
		return ;
	i = 0;
	while (array[i])									// Recorre cada string en el array y lo libera.
	{
		free(array[i]);
		i++;
	}
	free(array);										// Finalmente, libera el propio array.
}

void	free_game(t_cub *game)							// Libera todos los recursos asociados al juego.
{
	int i;

	i = -1;
	while (game->map[++i])								// Libera cada fila del mapa.
		free(game->map[i]);
	if (game->player)									// Libera la estructura del jugador si existe.
		free(game->player);
	free_coor(&game->coor);								// Libera las coordenadas y texturas.
	if (game->fd != -1)									// Si el archivo está abierto, lo cierra.
		close(game->fd);
	if (game->init)										// Termina la instancia de MLX si está inicializada.
		mlx_terminate(game->init);
	free(game);											// Finalmente, libera la estructura principal del juego.
}