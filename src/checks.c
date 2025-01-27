/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:42:15 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/27 18:42:08 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_check_map_closed(t_cub *game)																			// Comprueba si el mapa esta cerrado por paredes
{
	int	i;																										// Índice para recorrer filas del mapa.
	int	j;																										// Índice para recorrer columnas del mapa.
	int	len;																									// Longitud de la primera fila del mapa.

	i = 0;																										// Inicializamos el índice de filas a 0.
	j = 0;																										// Inicializamos el índice de columnas a 0.
	len = ft_strlen_cub3d(game->map[i]);																		// Obtenemos la longitud de la primera fila del mapa.

																												// Verificamos la primera fila del mapa.
	while (game->map[0][j])																						// Recorremos la primera fila.
	{
		if (game->map[0][j] != '1' && game->map[0][j] != ' ')													// Si algún carácter no es '1' o espacio.
			return (0);																							// Retornamos 0 indicando que no está cerrado.
		j++;																									// Avanzamos al siguiente carácter.
	}
	j = 0;																										// Reiniciamos el índice de columnas.
																												// Verificamos la última fila del mapa.
	while (game->map[game->coor->map_rows - 1][j])																// Recorremos la última fila.
	{
		if (game->map[game->coor->map_rows - 1][j] != '1' && game->map[game->coor->map_rows - 1][j] != ' ')
			return (0);																							// Retornamos 0 si algún carácter no es válido.
		j++;																									// Avanzamos al siguiente carácter.
	}
																												// Verificamos los bordes laterales de todas las filas.
	while (i < game->coor->map_rows)																			// Recorremos todas las filas.
	{
		if (!game->map[i])																						// Verificamos si la fila es nula.
			return (0);																							// Retornamos 0 si no hay fila.
		if (game->map[i][0] != '1' && game->map[i][0] != ' ')													// Comprobamos el primer carácter de la fila.
			return (0);																							// Retornamos 0 si no es válido.
		if (game->map[i][len - 1] != '1' && game->map[i][len - 1] != ' ')										// Comprobamos el último carácter de la fila.
			return (0);																							// Retornamos 0 si no es válido.
		i++;																									// Avanzamos a la siguiente fila.
	}
	return (1);																									// Retornamos 1 si el mapa está cerrado correctamente.
}

int	ft_check_valid_characters(t_cub *game)																		// Comprueba si el mapa contiene solo caracteres válidos.
{
	int		i;																									// Índice para recorrer filas.
	int		j;																									// Índice para recorrer columnas.
	char	c;																									// Carácter actual.

	i = 0;																										// Inicializamos el índice de filas.
	if (!game || !game->map)																					// Verificamos si el juego o el mapa son nulos.
	{
		printf("Error: game or game->map is NULL\n");															// Mostramos un error.
		return (0);																								// Retornamos 0 indicando fallo.
	}
	while (game->map[i])																						// Recorremos todas las filas del mapa.
	{
		if (!game->map[i])																						// Verificamos si alguna fila es nula.
		{
			printf("Error: game->map[%d] is NULL\n", i);														// Mostramos un error.
			return (0);																							// Retornamos 0.
		}
		j = 0;																									// Inicializamos el índice de columnas.
		while (game->map[i][j])																					// Recorremos cada carácter de la fila.
		{
			c = game->map[i][j];																				// Obtenemos el carácter actual.
			if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ')				// Comprobamos si el carácter no es válido.
			{
				printf("Error: Invalid character '%c' at (%d, %d)\n", c, i, j);									// Mostramos un error con el carácter y su posición.
				return (0);																						// Retornamos 0.
			}
			j++;																								// Avanzamos al siguiente carácter.
		}
		i++;																									// Avanzamos a la siguiente fila.
	}
	return (1);																									// Retornamos 1 si todos los caracteres son válidos.
}

int	ft_check_file(char *str)																					// Comprueba si el archivo tiene extensión .cub y si existe.
{
	int		len;																								// Longitud del string del nombre del archivo.

	remove_newline(str);																						// Eliminamos el salto de línea al final del string, si existe.
	len = ft_strlen_cub3d(str);																					// Obtenemos la longitud del string.
	if (len > 4 && ft_strncmp(&str[len - 4], ".cub", 4) == 0)													// Verificamos que la extensión es .cub.
	{
		if (access(str, F_OK) == 0)																				// Comprobamos si el archivo existe.
			return (1);																							// Retornamos 1 si existe y tiene la extensión correcta.
	}
	return (0);																									// Retornamos 0 si no cumple con los requisitos.
}
