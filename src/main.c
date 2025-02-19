/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:17:11 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/12 12:34:07 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	*game;															// Declara un puntero a la estructura t_cub, que almacena la información del juego.

	if (argc != 2)															// Verifica que se pase exactamente un argumento adicional (nombre del archivo).
		return (ft_error(NULL, 0, "Invalid number of arguments")), 1;		// Muestra un error si el número de argumentos no es válido.
	if (WIN_HEIGHT <= 0 || WIN_WIDTH <= 0)									// Comprueba que las dimensiones de la ventana sean válidas.
		ft_error(NULL, 1, "No valid measures");								// Muestra un error si las dimensiones no son correctas.
	game = ft_calloc(1, sizeof(t_cub));										// Reserva memoria para la estructura game e inicializa a 0.
	if (!game)																// Verifica si la asignación de memoria falló.
		return (1);															// Si no se pudo asignar memoria, finaliza el programa.
	ft_init_game(game);														// Inicializa la estructura game con valores predeterminados.
	ft_check_file(game,argv[1]);											// Verifica y procesa el archivo de configuración o mapa.
	ft_get_map(game, NULL, NULL);											// Carga el mapa en la estructura game.
	ft_check_color(game, game->coor.floor, &game->coor.t_floor);			// Verifica y convierte el color del suelo.
	ft_check_color(game, game->coor.ceiling, &game->coor.t_ceiling);		// Verifica y convierte el color del techo.
	ft_check_map(game, -1, -1);												// Verifica la validez del mapa (bordes cerrados, elementos correctos, etc.).
	//open_textures
	ft_mlx_init(game);														// Inicializa la librería gráfica MiniLibX y configura la ventana del juego.
	free_game(game);														// Libera la memoria y recursos utilizados por la estructura game.
	return (0);																// Finaliza el programa correctamente.
}