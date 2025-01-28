/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:45:57 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/28 20:05:11 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_color	ft_parse_color(char *line)																					// Parsear un color desde una línea de texto.
{
	t_color color;																									// Estructura para almacenar el color (RGB).
	char **rgb;																										// Array de strings para los valores R, G y B.

	rgb = ft_split(line, ',');																						// Dividimos la línea en componentes R, G, B usando la coma como separador.
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])																		// Verificamos que se obtuvieron los 3 componentes.
		ft_error("Error: Invalid color format");																	// Si no, mostramos un error y terminamos el programa.
																													// Convertimos cada componente de texto a entero.
	color.r = ft_atoi(rgb[0]);																						// Rojo
	color.g = ft_atoi(rgb[1]);																						// Verde
	color.b = ft_atoi(rgb[2]);																						// Azul

																													// Liberar la memoria de ft_split
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255 || color.b < 0 || color.b > 255)
		ft_error("Invalid RGB value (must be 0-255)");
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	return (color);																									// Retornamos el color parseado
}

void	ft_parse_texture_or_color(t_cub *game, char *line)															// Parsear una línea para identificar y guardar texturas o colores.
{
																													// Verificamos cada prefijo para determinar qué propiedad del juego estamos configurando.
	if (ft_strncmp(line, "NO ", 3) == 0)																			// Textura norte.
		game->coor->north = ft_strdup(&line[3]);																	// Guardar la ruta de la textura norte
	else if (ft_strncmp(line, "SO ", 3) == 0)																		// Textura sur.
		game->coor->south = ft_strdup(&line[3]);																	// Guardar la ruta de la textura sur
	else if (ft_strncmp(line, "WE ", 3) == 0)																		// Textura oeste
		game->coor->west = ft_strdup(&line[3]);																		// Guardar la ruta de la textura oeste
	else if (ft_strncmp(line, "EA ", 3) == 0)																		// Textura este
		game->coor->east = ft_strdup(&line[3]);																		// Guardar la ruta de la textura este
	else if (ft_strncmp(line, "F ", 2) == 0)																		// Color del suelo
		game->coor->floor_color = ft_parse_color(&line[2]);															// Parsear el color del suelo
	else if (ft_strncmp(line, "C ", 2) == 0)																		// Color del techo
		game->coor->ceiling_color = ft_parse_color(&line[2]);														// Parsear el color del techo
}

int	ft_is_texture_or_color(char *line)																				// Determina si una línea contiene un identificador de textura o color.
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||										// Comparamos el inicio de la línea con cada posible identificador.
		ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 ||
		ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (1);																									// Es una textura o color
	return (0);																										// No es una textura o color
}
void	ft_check_map_size(t_cub *game, char *filename)																	// Cargar los datos del juego desde un archivo .cub.
{
	int		fd;																										// Descriptor de archivo.
	char	*line;																									// Línea actual leída del archivo
	int	map_started = 0;																							// Indica si ya empezamos a leer el mapa
	int	i = 0;																										// Índice para las líneas del mapa.

	fd = open(filename, O_RDONLY);																					// Abrimos el archivo en modo solo lectura.
	if (fd < 0)																										// Verificamos si el archivo se abrió correctamente
		ft_error("Error: Couldn't open the map file");
	line = get_next_line(fd);																						// Leemos el archivo línea por línea.
	while (line)
	{
		if (ft_strlen(line) == 0 && map_started)																	// Si encontramos una línea vacía después de comenzar el mapa, mostramos un error.
			ft_error("Error: Empty line in map");
		if (line[ft_strlen(line) - 1] == '\n')																		// Eliminar el salto de línea al final de la línea (si existe)
			line[ft_strlen(line) - 1] = '\0';
		if (line[0] != '\0')																						// Si la línea no está vacía
		{
			if (ft_is_texture_or_color(line))																		// Si la línea contiene un identificador de textura o color
				ft_parse_texture_or_color(game, line);																// Parseamos la textura o el color.
			else
			{
				if (!map_started)																					// Si no es una textura o color, es parte del mapa
				{
					map_started = 1;																				// Empezamos a leer el mapa
				}
				i++;																								// Incrementamos el índice del mapa.
				game->coor->map_rows++;																				// Incrementamos el contador de filas del mapa.
			}
		}
		free(line);																									// Liberar la línea leída
		line = get_next_line(fd);																					// Leemos la siguiente línea
	}
	game->map = (char **)malloc(sizeof(char *) * (game->coor->map_rows + 1));										// Redimensionamos la memoria del mapa para ajustarla al número de filas leídas.
	if (!game->map)																									// Verificamos si la redimensión fue exitosa.
		ft_error("Error: Couldn't reallocate memory for the map");
	game->map[game->coor->map_rows] = NULL;																			// Terminar el mapa con NULL
	if (!game->coor->north || !game->coor->south || !game->coor->west || !game->coor->east)
	ft_error("Error: Missing textures");
	if (game->coor->floor_color.r == -1 || game->coor->ceiling_color.r == -1)
	ft_error("Error: Missing colors");
	close(fd);																										// Cerrar el archivo
}

void	ft_create_map(t_cub *game, char *filename)
{
	
}