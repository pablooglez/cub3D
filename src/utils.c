/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:53:44 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/07 19:47:56 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	change_spaces(t_cub *game)								// Función para cambiar los espacios en el mapa por '1' (paredes).
{
	int	y;
	int	x;

	y = -1;
	while (game->map[++y])										// Recorre cada fila del mapa.
	{
		x = -1;
		while (game->map[y][++x])								// Recorre cada carácter en la fila.
			if (game->map[y][x] == ' ')							// Si encuentra un espacio en blanco...
				game->map[y][x] = '1';							// Lo reemplaza por '1' (pared).
	}
}

int	ft_find_char_index(char *s)									// Función para encontrar el índice del primer carácter no espacio en una cadena.
{
	int		i;

	i = 0;
	while (s && s[i] && !ft_isspace(s[i]))						// Recorre la cadena mientras haya caracteres que no sean espacios.
		i++;
	return (i);													// Retorna el índice del primer espacio en blanco o final de la cadena.
}

int	ft_is_whitespace_only(char *line)							// Función para verificar si una línea contiene solo espacios en blanco.
{
	int	i;

	i = 0;
	while (line && line[i])										// Recorre la línea carácter por carácter.
	{
		if (line[i] != ' ' && (line[i] < 9 || line[i] > 13))	// Si encuentra un carácter que no es un espacio ni un carácter de tabulación/salto de línea, retorna 0.
			return (0);
		i++;
	}
	return (1);													// Retorna 1 si toda la línea contiene solo espacios en blanco.
}