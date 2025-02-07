/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:42:15 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/07 19:43:12 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	ft_check_character(t_cub *game, char current, char next)					// Función para verificar si un carácter en el mapa es válido.
{
	if (!ft_strchr("10NSWE ", current))													// Verifica si el carácter actual es válido ('1', '0', 'N', 'S', 'W', 'E' o espacio).
		return (ft_error(game, 1, "Invalid character on map."), 0);
	else if (current == '1' || current == ' ')											// Si es '1' (pared) o un espacio, es correcto.
		return (1);
	else if (current == '0' && (!ft_strchr("10NSWE", next) || !next))					// Si es '0' (suelo) y el siguiente carácter no es válido o está vacío, error.
		return (ft_error(game, 1, "Invalid map."), 0);
	else if (ft_strchr("NSWE", current) && (!ft_strchr("10", next) || !next))			// Si es un carácter de jugador ('N', 'S', 'W', 'E') y el siguiente no es válido, error.
		return (ft_error(game, 1, "Invalid map."), 0);
	return (1);
}

static int	ft_check_walls(t_cub *game, int y, int x)									// Función para verificar que el mapa esté rodeado por paredes.
{
		if (ft_strchr("0NSWE", game->map[y][x]) && (y == 0 || !game->map[y - 1]))		// Si el carácter es '0' o un jugador y está en una posición incorrecta, error.
			return (ft_error(game, 1, "Invalid map"), 0);
		else if (ft_strchr("0NSWE", game->map[y][x]) && !game->map[y + 1])
			return (ft_error(game, 1, "Invalid map."), 0);
		else if (ft_strchr("0NSWE", game->map[y][x])
			&& (x == 0 || !game->map[y][x - 1]))
			return (ft_error(game, 1, "Invalid map."), 0);
		else if (ft_strchr("0NSWE", game->map[y][x]) && !game->map[y][x + 1])
			return (ft_error(game, 1, "Invalid map."), 0);
		return (1);
}

void	fill_map_with_spaces(t_cub *game)												// Función para rellenar el mapa con espacios en líneas más cortas.
{
	size_t	max;
	int		y;
	char	*temp;

	y = -1;
	max = ft_strlen(game->map[0]);														// Obtiene la longitud de la primera línea.
	while(game->map[++y])																// Encuentra la línea más larga en el mapa.
		if (ft_strlen(game->map[y]) > max)
			max = ft_strlen(game->map[y]);
	y = -1;
	while(game->map[++y])																// Rellena las líneas más cortas con espacios hasta que tengan la misma longitud.
	{
		while (ft_strlen(game->map[y]) < max)
		{
			temp = game->map[y];
			game->map[y] =ft_strjoin(game->map[y], " ");
			free(temp);
		}
	}
}

static void	initialize_player_position(t_cub *game)										// Función para inicializar la posición del jugador en el mapa.
{
	int	y;
	int	x;

	y = -1;
	while (game->map[++y])																// Recorre el mapa fila por fila.
	{
		x = -1;
		while (game->map[y][++x])														// Recorre cada carácter en la fila.
		{
			if (ft_strchr("NSWE", game->map[y][x]))										// Si encuentra un jugador.
			{
				game->player->x = x + 0.5;												// Posición en X del jugador.
				game->player->y = y + 0.5;												// Posición en Y del jugador.
				game->player->view = game->map[y][x];									// Dirección en la que mira.
				game->n_player++;														// Aumenta el contador de jugadores.
			}
		}
	}
	if (game->n_player != 1)															// Si hay más de un jugador, lanza un error
		ft_error(game, 1, "Invalid number of players.");
}

void	ft_check_map(t_cub *game, int y, int x)											// Función principal para verificar el mapa y realizar validaciones.
{
	if (game->coor.n_coor != 6)															// Verifica si todas las texturas están definidas.
		ft_error (game, 1, "There is not a texture");
	if (!game->map[0])																	// Si no hay mapa, lanza un error.
		return (ft_error(game, 1, "There is not a map"));
	fill_map_with_spaces(game);															// Rellena el mapa con espacios en blanco si es necesario.
	while (game->map[++y])																// Recorre todo el mapa.
	{
		x = -1;
		while (game->map[y][++x])
		{
			ft_check_walls(game, y, x);													// Verifica que el mapa esté rodeado de paredes.
			if (y >= 0 && x >= 0)														// Verifica caracteres en posiciones adyacentes.
			{
				if (x > 0)
					ft_check_character(game, game->map[y][x], game->map[y][x - 1]);
				ft_check_character(game, game->map[y][x], game->map[y][x + 1]);
				if (y > 0)
					ft_check_character(game, game->map[y][x], game->map[y - 1][x]);
				if (game->map[y] && game->map[y + 1])
					ft_check_character(game, game->map[y][x], game->map[y + 1][x]);
			}
		}
	}
	change_spaces(game);																// Modifica los espacios en el mapa.
	initialize_player_position(game);													// Inicializa la posición del jugador.
}
