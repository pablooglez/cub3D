/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelope <albelope@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:05:27 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/19 10:01:47 by albelope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void	load_textures(t_cub *game)																// Carga las texturas desde archivos PNG y las asigna a la estructura del juego
{
																								// Carga cada textura usando la función mlx_load_png()
	game->coor.txt_north_i = mlx_load_png(game->coor.north);
	game->coor.txt_south_i = mlx_load_png(game->coor.south);
	game->coor.txt_west_i = mlx_load_png(game->coor.west);
	game->coor.txt_east_i = mlx_load_png(game->coor.east);
																								// Si alguna textura no se cargó correctamente, muestra un error y detiene el programa
	if (!game->coor.txt_north_i || !game->coor.txt_south_i
		|| !game->coor.txt_west_i || !game->coor.txt_east_i)
		ft_error(game, 1, "Failed to load textures");
	else
	{
		printf("texturas ok.\n");
		printf("north: %s\n", game->coor.north);
		printf("South: %s\n", game->coor.south);
		printf("West: %s\n", game->coor.west);
		printf("East: %s\n", game->coor.east);
	}
}

void	ft_mlx_init(t_cub *game)																// Inicializa MLX42 y configura el bucle principal del juego
{
	mlx_set_setting (MLX_STRETCH_IMAGE, true);													// Permite estirar la imagen al tamaño de la ventana
	game->init = mlx_init (WIN_WIDTH, WIN_HEIGHT, "cub3d", true);								// Inicializa MLX con tamaño de ventana
	if (!game->init)																			// Si falla la inicialización, muestra un error y detiene el programa
		ft_error(game, 1, "Failed to initialize MLX42");														
	game->img_window = mlx_new_image(game->init, WIN_WIDTH, WIN_HEIGHT);						// Crea una imagen para renderizar
	mlx_image_to_window(game->init, game->img_window, 0, 0);									// Añade la imagen a la ventana
	load_textures(game);																		
	mlx_loop_hook(game->init, put_textures, game);												// Asigna la función put_textures al bucle de MLX
	mlx_key_hook(game->init, &ft_keymoves, game);
	mlx_loop_hook(game->init, ft_process_movement, game);										// Manejo de eventos de teclado (comentado)
	mlx_loop(game->init);																		// Inicia el bucle principal de MLX
}
