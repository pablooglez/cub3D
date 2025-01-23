/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:23:58 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/23 19:23:10 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Librerías necesarias para usar las funciones permitidas en el proyecto
# include <unistd.h>						// read, write y close
# include <stdio.h>							// printf
# include <stdlib.h>						// malloc, free
# include <string.h>						//strerror
# include <errno.h>							// perror
# include <fcntl.h>							// open
# include <sys/time.h>						// gettimeofday
# include <math.h>							// sin, cos, tan, sqrt, pow ...
# include "../Libft/libft.h"				// Libft
# include "../Libft/get_next_line_bonus.h"	//Get_next_line
# include "../MLX42/include/MLX42/MLX42.h"	// MLX42

// Constantes del programa
# define WIN_WIDTH 1920						// Ancho de la ventana
# define WIN_HEIGHT 1080					// Altura de la ventana
# define FOV 60								// Campo de vision del jugador
# define P_SPEED 2							// Velocidad de movimiento del jugador
# define R_SPEED 0.045						// Velocidad de rotación del jugador

// Identificadores para la configuración del archivo .pub
# define ID_NO "NO"							// ID para la textura norte
# define ID_SO "SO"							// ID para la textura sur
# define ID_WE "WE"							// ID para la textura oeste
# define ID_EA "EA"							// ID para la textura este
# define ID_F "F"							// ID para color del suelo
# define ID_C "C"							// ID para el color del cielo


// Estructura para almacenar colores RGB
typedef struct s_color						// Estructura para almacenar colores RGB
{
	int	r;									// Valor del canal rojo
	int	g;									// Valor del canal verde
	int	b;									// Valor del canal azul
}	t_color;

// Estructura para representar al jugador (Usamos float para mejorar precisión de calculos y no sobrecargar la memoria)
typedef struct s_player
{
	float	x;								// Posicion en el eje X
	float	y;								// Posicion en el eje Y
	float	angle;							// Ángulo de visión del jugador 
	float	move_speed;						// Velocidad de movimiento del jugador
	float	rot_speed;						// Velocidad de rotación del jugador
}	t_player;

// Estructura para almacenar la configuración del mapa
typedef struct s_coor						// Estructura para almacenar las coordenadas del mapa
{
	char	*north;							// Ruta del norte
	char	*south;							// Ruta del sur
	char	*west;							// Ruta del oeste
	char	*east;							// Ruta del este
	t_color	floor_color;					// Color del suelo
	t_color	ceiling_color;					// Color del cielo
	int		map_rows;						// Número de filas del mapa
	int		map_cols;						// Número de columnas en el mapa
}	t_coor;

// Estructura principal del juego
typedef struct game
{
	mlx_t			*init;					// Conexión con la MLX42
	mlx_image_t		*img_window;			// Imagen de la ventana
	int				fd;						// Descriptor de archivo del .cub
	char			**map;					// Matriz del mapa
	t_coor			*coor;					// Configuración del mapa (texturas, colores, ... etc)
	t_player		*player;				// Información del jugador
	int				n_player;				// Número de posiciones de inicio del jugador
}	t_cub;


//----------------CHECKS--------------------//
int				ft_check_map_closed(t_cub *game);
int				ft_check_valid_characters(t_cub *game);
int				ft_check_file(char *str);

//----------------ERROR---------------------//
void			ft_error(char *msg);

//----------------FLOOD-FILL----------------//


//----------------LOAD_GAME----------------//
void			ft_load_game(t_cub *game, char *filename);

//----------------UTILS---------------------//
void			print_map(t_cub *game);
void			remove_newline(char *str);
int				ft_strlen_cub3d(char *str);
void			ft_init_game(t_cub *game);
#endif