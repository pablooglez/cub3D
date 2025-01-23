/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:45:57 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/23 19:34:52 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_color ft_parse_color(char *line)
{
    t_color color;
    char **rgb;

    rgb = ft_split(line, ',');
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
        ft_error("Error: Invalid color format");

    color.r = ft_atoi(rgb[0]);
    color.g = ft_atoi(rgb[1]);
    color.b = ft_atoi(rgb[2]);

    // Liberar la memoria de ft_split
    free(rgb[0]);
    free(rgb[1]);
    free(rgb[2]);
    free(rgb);

    return (color);
}

void ft_parse_texture_or_color(t_cub *game, char *line)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
        game->coor->north = ft_strdup(&line[3]);  // Guardar la ruta de la textura norte
    else if (ft_strncmp(line, "SO ", 3) == 0)
        game->coor->south = ft_strdup(&line[3]);  // Guardar la ruta de la textura sur
    else if (ft_strncmp(line, "WE ", 3) == 0)
        game->coor->west = ft_strdup(&line[3]);   // Guardar la ruta de la textura oeste
    else if (ft_strncmp(line, "EA ", 3) == 0)
        game->coor->east = ft_strdup(&line[3]);   // Guardar la ruta de la textura este
    else if (ft_strncmp(line, "F ", 2) == 0)
        game->coor->floor_color = ft_parse_color(&line[2]);  // Parsear el color del suelo
    else if (ft_strncmp(line, "C ", 2) == 0)
        game->coor->ceiling_color = ft_parse_color(&line[2]);  // Parsear el color del techo
}
int ft_is_texture_or_color(char *line)
{
    if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
        ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 ||
        ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
        return (1);  // Es una textura o color
    return (0);  // No es una textura o color
}
void ft_load_game(t_cub *game, char *filename)
{
    int fd;
    char *line;
    int map_started = 0;  // Indica si ya empezamos a leer el mapa
    int i = 0;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        ft_error("Error: Couldn't open the map file");

    // Inicializar el mapa
    game->map = (char **)malloc(sizeof(char *) * 100);  // Tamaño inicial (ajustar según necesidad)
    if (!game->map)
        ft_error("Error: Couldn't allocate memory for the map");

    // Leer el archivo línea por línea
    line = get_next_line(fd);
    while (line)
    {
        // Eliminar el salto de línea al final de la línea (si existe)
        if (line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';

        // Si la línea no está vacía y no es un comentario (empieza con '#')
        if (line[0] != '\0' && line[0] != '#')
        {
            // Si la línea contiene un identificador de textura o color
            if (ft_is_texture_or_color(line))
            {
                // Parsear la textura o el color
                ft_parse_texture_or_color(game, line);
            }
            else
            {
                // Si no es una textura o color, es parte del mapa
                if (!map_started)
                {
                    map_started = 1;  // Empezamos a leer el mapa
                }

                // Guardar la línea en el mapa
                game->map[i] = ft_strdup(line);
                if (!game->map[i])
                    ft_error("Error: Couldn't allocate memory for a map line");
                i++;
                game->coor->map_rows++;
            }
        }
        free(line);  // Liberar la línea leída
        line = get_next_line(fd);
    }

    // Ajustar el tamaño del mapa
    game->map = (char **)realloc(game->map, sizeof(char *) * (game->coor->map_rows + 1));
    if (!game->map)
        ft_error("Error: Couldn't reallocate memory for the map");
    game->map[game->coor->map_rows] = NULL;  // Terminar el mapa con NULL

    close(fd);  // Cerrar el archivo
}