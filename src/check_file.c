/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:06:28 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/07 18:22:51 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_check_file(t_cub *game, char *argv)
{
	char	*archive;
	char	*backslash;

	archive = ft_strrchr(argv, '.');												// Busca la última aparición de '.' en el nombre del archivo (para la extensión).
	backslash = ft_strrchr(argv, '/');												// Busca la última aparición de '/' en el nombre del archivo (para verificar la ruta).
																					
	if (backslash && (!ft_strcmp (&backslash[1], ".cub") || backslash[1] == '.'))	// Verifica si el archivo es oculto (empieza con un punto después de una barra).
		ft_error(game, 1, "Can't have hidden files");								// Muestra error si el archivo es oculto.
	if (!archive || ft_strcmp(archive, ".cub"))										// Verifica si la extensión del archivo no es ".cub" o si no tiene extensión.
		return (ft_error(game, 1, "Incorrect Extension"));							// Muestra error si la extensión es incorrecta.
	if (ft_strlen(archive) == ft_strlen(argv))										// Verifica si el nombre del archivo empieza con un punto, lo que indica que es un archivo oculto.
		ft_error(game, 1, "Can't have hidden files");								// Muestra error si el archivo es oculto.
	game->fd = open(argv, O_RDONLY);												// Intenta abrir el archivo en modo solo lectura.
	if (game->fd < 0)																// Si la apertura falla, muestra un error.
		return (ft_error(game, 1, "Can't open file"));
}