/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:45:57 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/07 19:26:57 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*get_and_save_coor(t_cub *game, char *dst, char *coor, char *line)			// Función auxiliar para obtener y guardar las coordenadas de texturas y colores
{
	int	i;
	
	if (dst)																			// Si ya se ha guardado esta coordenada previamente, la devuelve.
		return (dst);
	if (!line || !*line || line[0] == '\n') return (NULL);								// Si la línea está vacía o es un salto de línea, retorna NULL.
	i = ft_find_char_index(line);														// Encuentra la posición del primer espacio o separador en la línea.
	if (i && !ft_strncmp(line, coor, i))												// Verifica si la línea empieza con la clave esperada (NO, SO, WE, EA, F, C).
	{
		if (dst)																		// Si ya se asignó esta coordenada antes, se lanza un error.
		{
			ft_error(game, 1, "Duplicate texture");
		}
		game->coor.n_coor++;															// Incrementa el contador de coordenadas leídas.
		line += i;																		// Avanza en la línea hasta el valor después del identificador.
		while (ft_isspace(*line))														// Omite los espacios en blanco.
			line++;
		return (ft_substr(line, 0, ft_strlen(line) - 1));								// Extrae la coordenada y la retorna.
	}
	return (NULL);																		// Si la línea no corresponde a la coordenada buscada, retorna NULL.
}

static int	ft_save_coor(t_cub *game, char *line, int *flag)							// Guarda las coordenadas de texturas y colores en la estructura game->coor
{
	int i;

	i = ft_find_char_index(line);														// Encuentra la posición del primer separador en la línea.
	if (i && *line != '\n' && ft_strlen(line) > 0										// Verifica si la línea es válida y no está vacía.
		&& ft_strncmp(line, "NO", i)													// Verifica que no sea una coordenada válida (NO, SO, WE, EA, F, C).
		&& ft_strncmp(line, "SO", i)
		&& ft_strncmp(line, "WE", i)
		&& ft_strncmp(line, "EA", i)
		&& ft_strncmp(line, "F", i)
		&& ft_strncmp(line, "C", i)
		&& game->coor.n_coor < 6)														// Si aún no se han leído todas las coordenadas necesarias.
			(*flag) = 1;																// Marca un error si hay una línea desconocida.
	
	game->coor.north = get_and_save_coor(game, game->coor.north, "NO", line);			// Asigna las texturas y colores a las coordenadas correspondientes.
	game->coor.south = get_and_save_coor(game, game->coor.south, "SO", line);
	game->coor.west = get_and_save_coor(game, game->coor.west, "WE", line);
	game->coor.east = get_and_save_coor(game, game->coor.east, "EA", line);
	game->coor.floor = get_and_save_coor(game, game->coor.floor, "F", line);
	game->coor.ceiling = get_and_save_coor(game, game->coor.ceiling, "C", line);
	if (game->coor.n_coor >= 6)															// Si ya se han leído todas las coordenadas necesarias.
		game->start_map = 1;															// Marca el inicio de la lectura del mapa.
	return (game->start_map);															// Retorna si el mapa ha comenzado a leerse.
}

void	ft_get_map(t_cub *game, char *aux, char *result)								// Función para leer el archivo y obtener el mapa
{
	char	*line;
	int		flag;
	int i;

	(void)aux;																			// No se usa aux, pero se mantiene para evitar warnings.
	(void)result;																		// No se usa result, pero se mantiene para evitar warnings.

	i = 0;
	flag = 0;
	line = get_next_line(game->fd);														// Lee la primera línea del archivo.
	while (line)																		// Mientras haya líneas en el archivo.
	{
		if (!game->start_map)															// Si todavía no se ha empezado a leer el mapa.
			if (ft_save_coor(game, line, &flag))										// Guarda las coordenadas y revisa si se completa la configuración.
			{
				free(line);																// Libera la memoria de la línea leída.
				line = get_next_line(game->fd);											// Lee la siguiente línea.
				continue;																// Vuelve al inicio del bucle.
			}
		if (game->start_map == 1)														// Si se completó la configuración y empieza la lectura del mapa.
		{
			if (ft_is_whitespace_only(line))											// Si la línea es solo espacios en blanco, se omite.
			{
				free(line);
				line = get_next_line(game->fd);
				continue;
			}
			game->start_map = 2;														// Se marca que el mapa ha comenzado.
		}
		if (game->start_map == 2)														// Se está leyendo el mapa.
		{
			if (ft_is_whitespace_only(line))											// Si la línea es solo espacios en blanco, marca un error.
				flag = 9;
			else
			{
				if (line && line[0] && line[ft_strlen(line) - 1] == '\n')				// Si la línea termina en '\n', lo elimina.
					line[ft_strlen(line) - 1] = '\0';
				game->map[i++] = ft_strdup(line);										// Guarda la línea en el array de mapa.
				if (i == 1024)															// Si el mapa supera el límite de 1024 líneas.
					flag = 8;
			}
			
		}
		free(line);																		// Libera la memoria de la línea leída.
		if (flag > 0)																	// Si hay un error, se interrumpe la lectura.
			break;
		line = get_next_line(game->fd);													// Lee la siguiente línea.
	}
	game->map[i] = NULL;																// Termina el array del mapa con NULL.
	if (result)																			// Si result tenía algún contenido previo, lo libera.
		free(result);
	if (flag == 8)																		// Si se pasó del límite de líneas permitidas en el mapa.
		ft_error(game, 1, "Map too big");												// Muestra un error por mapa demasiado grande.
	if (flag)																			// Si hubo algún otro error.
		ft_error(game, 1, "Unrecognized line");											// Muestra un error por línea desconocida.
}

