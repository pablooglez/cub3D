/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:01:31 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/11 17:32:48 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void ft_init_game(t_cub *game)
{
	game->player = ft_calloc(1, sizeof(t_player));			// Reserva memoria para la estructura del jugador e inicializa a 0.
	if (!game->player)										// Verifica si la asignación de memoria falló.
		ft_error(game, 1, "Malloc failed");					// Muestra un error y finaliza el programa si no se pudo asignar memoria.
	game->player->x = WIN_WIDTH / 2;
	game->player->y = WIN_HEIGHT / 2;
	game->player->view = 0;
	game->fd = -1;											// Inicializa el descriptor de archivo en -1 (indica que aún no se ha abierto ningún archivo).
}