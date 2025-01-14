/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:23:58 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/14 21:38:43 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h> // read, write y close
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <string.h> //strerror
# include <errno.h> // perror
# include <fcntl.h> // open
# include <sys/time.h> // gettimeofday
# include <math.h> // sin, cos, tan, sqrt, pow ...
# include "../Libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define FOV 60

typedef struct s_color //Estructura para almacenar colores RGB
{
	int	r;
	int	g;
	int	b;
} t_color;

typedef struct s_coor // Estructura para almacenar las coordenadas del mapa
{
	char	*north; // Ruta del norte
	char	*south; // Ruta del sur
	char	*west; // Ruta del oeste
	char	*east; //Ruta del este
	t_color	floor_color; // Color del suelo
	t_color	ceiling_color; // Color del cielo
	char	**map; // Matriz del mapa
	int		map_rows; // Número de filas del mapa
	int		map_cols; // Número de columnas en el mapa
} t_config;



#endif