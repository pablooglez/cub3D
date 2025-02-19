/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:05:27 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/12 12:32:12 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//templates

static unsigned int	get_rgba(t_color *color);

void fill_world_data(t_cub *game)																// Llena los datos del mundo, asignando valores iniciales a los rayos del juego
{
	int a;																						// Variable usada para definir la longitud de los rayos
	for (int i = 0; i < WIN_WIDTH; i++)															// Recorre cada columna de la ventana
	{
		game->rays[i].column = i;																// Asigna el índice de la columna
		game->rays[i].side = EAST;																// Por defecto, los rayos miran al Este
																								// Define diferentes longitudes y lados en función de la posición de la columna
		if (i < 400) a = 600;
		if (i >= 400 && i <= 800) { a++; game->rays[i].side = SOUTH; }
		if (i > 800 && i <= 900) game->rays[i].side = WEST;
		if (i > 900 && i <= 1200) a = 100;
		if (i > 1200) a = 1200;
		game->rays[i].length = a;																// Asigna la longitud calculada al rayo
	}
}

void draw_wall(t_cub *game, int x, int y, int side) {											// Dibuja un "muro" en la posición (x, y) con un color basado en el lado que representa

	uint32_t color;																				// Color en formato RGBA
	t_color w_color;																			// Estructura para definir los colores

																								// Asigna un color diferente según el lado del muro
	if (side == NORTH) { w_color.r = 135; w_color.g = 206; w_color.b = 235; }					// Azul claro
	if (side == SOUTH) { w_color.r = 255; w_color.g = 165; w_color.b = 0; }						// Naranja
	if (side == WEST) { w_color.r = 128; w_color.g = 0; w_color.b = 128; }						// Púrpura
	if (side == EAST) { w_color.r = 255; w_color.g = 255; w_color.b = 0; }						// Amarillo
	color = get_rgba(&w_color);																	// Convierte la estructura t_color a RGBA
	mlx_put_pixel(game->img_window, x, y, color);												// Pinta el píxel en la imagen
}

//templates


static unsigned int	get_rgba(t_color *color)													// Convierte una estructura t_color a un valor RGBA en formato uint32_t
{
	return ((unsigned int)color->r << 24 | (unsigned int)color->g << 16
		| (unsigned int)color->b << 8 | 255);													// El último byte es 255 (opacidad máxima)
}

void	put_textures(void *param)																// Pinta los píxeles en pantalla, asignando texturas y colores al suelo, techo y paredes
{
	t_cub *game;

	game = (t_cub *) param;																		// Convierte el parámetro a la estructura del juego
	int i = 0;
	while (i < WIN_WIDTH)																		// Recorre cada columna de la ventana
	{
		int top = (WIN_HEIGHT / 2) - (game->rays[i].length / 2);								// Punto superior del muro
		int bottom = (WIN_HEIGHT / 2) + (game->rays[i].length - (game->rays[i].length / 2));	// Punto inferior
		int j = 0;
		while (j < WIN_HEIGHT)																	// Recorre cada fila de la ventana
		{
			if (j < top)																		// Si está por encima del muro, es el techo
				mlx_put_pixel(game->img_window, i, j, get_rgba(&game->coor.t_ceiling));
			else if (j >= top && j <= bottom)													// Si está dentro del rango del muro, dibuja la pared
				draw_wall(game, i, j, game->rays[i].side);
			else if (j > bottom)																// Si está debajo del muro, es el suelo
				mlx_put_pixel(game->img_window, i, j, get_rgba(&game->coor.t_floor));
			j++;
		}
		i++;
	}
	
}

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
}

void	ft_mlx_init(t_cub *game)																// Inicializa MLX42 y configura el bucle principal del juego
{
	mlx_set_setting (MLX_STRETCH_IMAGE, true);													// Permite estirar la imagen al tamaño de la ventana
	game->init = mlx_init (WIN_WIDTH, WIN_HEIGHT, "cub3d", true);								// Inicializa MLX con tamaño de ventana
	if (!game->init)																			// Si falla la inicialización, muestra un error y detiene el programa
		ft_error(game, 1, "Failed to initialize MLX42");
	load_textures(game);																		// Carga las texturas del juego
	game->img_window = mlx_new_image(game->init, WIN_WIDTH, WIN_HEIGHT);						// Crea una imagen para renderizar
	mlx_image_to_window(game->init, game->img_window, 0, 0);									// Añade la imagen a la ventana
	fill_world_data(game);																		// Configura los rayos del mundo
	mlx_loop_hook(game->init, put_textures, game);												// Asigna la función put_textures al bucle de MLX
	mlx_key_hook(game->init, &ft_keymoves, game);												// Manejo de eventos de teclado (comentado)
	//raycasting
	mlx_loop(game->init);																		// Inicia el bucle principal de MLX
}
