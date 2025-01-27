/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:53:44 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/27 19:07:42 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void remove_newline(char *str)										// Elimina el salto de línea ('\n') al final de una cadena
{
	int	len;

	len = ft_strlen_cub3d(str);										// Obtenemos la longitud de la cadena hasta el salto de línea
	if (len > 0 && str[len - 1] == '\n')							// Si la cadena termina en '\n'
		str[len - 1] = '\0';										// Lo reemplazamos por el carácter nulo
}

int	ft_strlen_cub3d(char *str)										// Calcula la longitud de una cadena hasta el salto de línea o el final de la cadena
{
	int	i;

	i = 0;
	if (!str)														// Si la cadena es NULL, retornamos 0
		return (0);
	while (str[i] && str[i] != '\n')								// Recorremos la cadena hasta encontrar '\n' o el final
		i++;
	return (i);														// Retornamos la longitud calculada
}

void ft_init_game(t_cub *game)										// Inicializa las estructuras principales del juego
{
	game->init = NULL;												// Puntero para la librería gráfica (por ejemplo, MLX)
	game->img_window = NULL;										// Puntero para la ventana del juego
	game->fd = -1;													// Descriptor de archivo inicializado a un valor inválido
	game->map = NULL;												// Inicializamos el mapa a NULL
	game->coor = malloc(sizeof(t_coor));							// Reservamos memoria para la estructura `t_coor`
	if (!game->coor)												// Verificamos si la asignación fue exitosa
		ft_error("Error: Failed to allocate memory for coor");
	game->coor->north = NULL;										// Ruta de textura norte
	game->coor->south = NULL;										// Ruta de textura sur
	game->coor->west = NULL;										// Ruta de textura oeste
	game->coor->east = NULL;										// Ruta de textura este
	game->coor->floor_color = (t_color){-1, -1, -1};				// Color del suelo
	game->coor->ceiling_color = (t_color){-1, -1, -1};				// Color del techo
	game->coor->map_rows = 0;										// Número de filas en el mapa
	game->coor->map_cols = 0;										// Número de columnas en el mapa
	game->player = malloc(sizeof(t_player));						// Reservamos memoria para la estructura `t_player`
	if (!game->player)												// Verificamos si la asignación fue exitosa
		ft_error("Error: Failed to allocate memory for player");
	game->player->x = -1;											// Posición X del jugador (inicialmente no definida)
	game->player->y = -1;											// Posición Y del jugador (inicialmente no definida)
	game->player->angle = 0;										// Ángulo inicial del jugador
	game->player->move_speed = P_SPEED;								// Velocidad de movimiento
	game->player->rot_speed = R_SPEED;								// Velocidad de rotación
																	// Inicializamos el contador de jugadores en el mapa
	game->n_player = 0;												// Indica que aún no se ha encontrado ningún jugador
}