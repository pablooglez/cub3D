/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:19:25 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/07 17:11:22 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_print_error(const char *msg)
{
	ft_putstr_fd("Error: ", 2);								// Imprime "Error: " en el descriptor de archivo 2 (stderr).
	ft_putendl_fd(msg, 2);									// Imprime el mensaje de error seguido de un salto de línea en stderr.
}

void	ft_error(t_cub *game, int use, const char *msg)
{
	ft_print_error(msg);									// Imprime el mensaje de error recibido.

	if (!use)												// Si use es 0, significa que el error está relacionado con el uso incorrecto del programa.
	{
		ft_print_error("Usage: ./cub3d Maps/map.cub");		// Imprime el mensaje de uso correcto del programa.
		return;												// Termina la función sin cerrar el programa.
	}
	free_game(game);										// Libera la memoria utilizada por game antes de salir.
	exit(EXIT_FAILURE);										// Termina el programa con un código de error.
}

